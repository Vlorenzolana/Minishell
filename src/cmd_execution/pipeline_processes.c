/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:18:35 by dalabrad          #+#    #+#             */
/*   Updated: 2025/09/09 07:49:27 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static void	close_safe(int *fd)
{
	if (fd && *fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

static void	child_stdio(t_data *d, size_t i)
{
	int	rfd;
	int	wfd;

	rfd = (i == 0) ? -1 : d->pipes[(i + 1) % 2][R_PIPE];
	wfd = (i == (size_t)(d->nbr_cmds - 1)) ? -1 : d->pipes[i % 2][W_PIPE];
	if (rfd >= 0)
		dup2(rfd, STDIN_FILENO);
	if (wfd >= 0)
		dup2(wfd, STDOUT_FILENO);
	close_safe(&d->pipes[0][R_PIPE]);
	close_safe(&d->pipes[0][W_PIPE]);
	close_safe(&d->pipes[1][R_PIPE]);
	close_safe(&d->pipes[1][W_PIPE]);
}

void	child_process(t_data *data, t_cmd *cmd, size_t i)
{
	child_stdio(data, i);
	if (cmd->file_in)
		file_in_redir(cmd);
	if (cmd->file_out)
		file_out_redir(cmd);
	command_exec(cmd, data);
	_exit(data->last_status);
}

static void	wait_all_children(t_data *data, t_cmd *head)
{
	int		st;
	int		status;
	t_cmd	*cur;

	status = 0;
	cur = head;
	while (cur)
	{
		if (cur->pid > 0 && waitpid(cur->pid, &st, 0) > 0)
		{
			if (WIFEXITED(st))
				status = WEXITSTATUS(st);
			else if (WIFSIGNALED(st))
				status = 128 + WTERMSIG(st);
		}
		cur = cur->next;
	}
	data->last_status = status;
}

void	parent_process(t_data *data, t_cmd *cmd, size_t i)
{
	if (i > 0)
		close_safe(&data->pipes[(i + 1) % 2][R_PIPE]);
	if (i < (size_t)(data->nbr_cmds - 1))
		close_safe(&data->pipes[i % 2][W_PIPE]);
	if (cmd->next == NULL)
	{
		close_safe(&data->pipes[0][R_PIPE]);
		close_safe(&data->pipes[0][W_PIPE]);
		close_safe(&data->pipes[1][R_PIPE]);
		close_safe(&data->pipes[1][W_PIPE]);
		wait_all_children(data, data->first_cmd);
	}
}