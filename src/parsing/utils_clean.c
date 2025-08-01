/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:15:13 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/06/21 16:49:31 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

// EXIT COMMAND
int	is_exit_command(char *line)
{
	if (!line)
	{
		printf("exit\n");
		return (1);
	}
	if (!ft_strcmp(line, "exit"))
	{
		free(line);
		return (1);
	}
	return (0);
}

// CLEAN STRUCT T_PIPES
t_pipes	*clean_struct(t_pipes *args)
{
	t_pipes	*temp;

	temp = NULL;
	while (args->next)
	{
		temp = args;
		args = args->next;
		free(temp);
		temp = NULL;
	}
	return (temp);
}

// FREE TOKENS
void	free_tokens_list(t_tokens *head)
{
	t_tokens	*tmp;

	while (head && head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}

// CLEAN-UP SEGMENTS/TOKENIZED-ARGS ARRAY
void	cleanup(char *line, char **segments, t_tokens **tokens, size_t n)
{
	size_t	j;

	free_array(segments);
	if (tokens)
	{
		j = 0;
		while (j < n)
			free_tokens_list(tokens[j++]);
		free(tokens);
	}
	free(line);
}
