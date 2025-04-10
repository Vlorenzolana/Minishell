/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:10:22 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/24 17:12:09 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	shell_echo(char **args, t_env **shell_envp)
{
	int		i;
	bool	nl_flag;

	i = 0;
	nl_flag = true;
	(void)shell_envp;
	if (!args || !args[0])
		return (EXIT_FAILURE);
	if (args[i] && !ft_strncmp("-n", args[i], ft_strlen(args[i])))
	{
		nl_flag = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}
