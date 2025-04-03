/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:08:15 by dalabrad          #+#    #+#             */
/*   Updated: 2025/04/03 16:53:57 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static int	export_pwd(t_env **shell_envp, char *pwd_path, char *pwd_type)
{
	char	**tmp;

	tmp = (char **)malloc(2 * sizeof(char *));
	if (!tmp)
		return (error_msg(MALLOC_ERROR));
	tmp[0] = ft_strjoin(pwd_type, pwd_path);
	if (!tmp[0])
	{
		free(tmp);
		return (error_msg(MALLOC_ERROR));
	}
	tmp[1] = NULL;
	shell_export(tmp, shell_envp);
	free_array(tmp);
	return (EXIT_SUCCESS);
}

static int	cd_check_args(char **args)
{
	if (array_size(args) != 1)
		return (error_msg(CD_ERROR));
	if (access(args[0], F_OK))
		return (error_msg_arg(CD_NO_DIR, args[0]));
	if (access(args[0], X_OK))
		return (error_msg_arg(CD_NO_PERM, args[0]));
	return (0);
}

int	shell_cd(char **args, t_env **shell_envp)
{
	char	*old_pwd;
	char	*pwd;
	int		status;

	if (!args || !args[0])
		return (EXIT_FAILURE);
	if (cd_check_args(args))
		return (EXIT_FAILURE);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (error_msg(MALLOC_ERROR));
	if (chdir(args[0]))
		return (free(old_pwd), error_msg(CHDIR_ERROR));
	status = export_pwd(shell_envp, old_pwd, "OLDPWD=");
	free(old_pwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error_msg(MALLOC_ERROR));
	status += export_pwd(shell_envp, pwd, "PWD=");
	free(pwd);
	return (status);
}
