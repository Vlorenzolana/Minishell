/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:29:51 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/06/27 19:25:07 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"
#include <unistd.h>
#include <stdio.h>

void	restore_stdio(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	reset_cmd_state(t_data *data, char *line, char **segments, t_tokens **tokens)
{
	free_cmd_list(data->first_cmd);
	data->first_cmd = NULL;
	cleanup(line, segments, tokens, 0); // <- Asegúrate de que cleanup acepta n = 0 sin fallar
}
