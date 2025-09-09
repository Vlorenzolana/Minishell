/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:26:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/09/09 07:53:49 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static int	run_external_single(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		st;

	pid = fork();
	if (pid < 0)
		return (error_msg(FORK_ERROR), 1);
	if (pid == 0)
	{
		if (cmd->file_in)
			file_in_redir(cmd);
		if (cmd->file_out)
			file_out_redir(cmd);
		command_exec(cmd, data);
		_exit(data->last_status);
	}
	if (waitpid(pid, &st, 0) < 0)
		return (error_msg(PIPE_ERROR), 1);
	if (WIFEXITED(st))
		return (WEXITSTATUS(st));
	if (WIFSIGNALED(st))
		return (128 + WTERMSIG(st));
	return (1);
}

void	one_cmd_pipeline(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->first_cmd;
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]))
		one_builtin_with_redir(data, cmd);
	else
		data->last_status = run_external_single(cmd, data);
}