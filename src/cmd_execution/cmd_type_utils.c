/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:46:09 by dalabrad          #+#    #+#             */
/*   Updated: 2025/09/01 23:53:58 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->file_in = NULL;
	cmd->file_out = NULL;
	cmd->append_out = false;
	cmd->pid = -1;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*last_cmd(t_cmd *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

size_t	number_of_cmds(t_cmd *head)
{
	size_t	n;

	n = 0;
	while (head)
	{
		++n;
		head = head->next;
	}
	return (n);
}

/* Pedida por main_utils.c, pipeline_processes.c, builtin_exit.c, etc. */
void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	size_t	i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		if (cmd->file_in)
			free(cmd->file_in);
		if (cmd->file_out)
			free(cmd->file_out);
		/* No liberar: append_out (bool), pid (pid_t) */
		free(cmd);
		cmd = tmp;
	}
}