/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:26:53 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/27 19:54:00 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void one_cmd_pipeline(t_data *data)
{
    t_cmd *cmd = data->first_cmd;
    int fd_in, fd_out;

    if (!cmd)
        return;
    if (is_builtin(cmd->args[0], data))
    {
        int saved_stdin = dup(STDIN_FILENO);
        int saved_stdout = dup(STDOUT_FILENO);
        fd_in = -1;
        fd_out = -1;

        if (cmd->file_in)
        {
            fd_in = open(cmd->file_in, O_RDONLY);
            if (fd_in < 0)
            {
                error_msg_arg(NO_PATH, cmd->file_in);
                return;
            }
            dup2(fd_in, STDIN_FILENO);
        }
        if (cmd->file_out)
        {
            int flags = O_CREAT | O_WRONLY | (cmd->append_out ? O_APPEND : O_TRUNC);
            fd_out = open(cmd->file_out, flags, 0644);
            if (fd_out < 0)
            {
                error_msg_arg(NO_PATH, cmd->file_out);
                return;
            }
            dup2(fd_out, STDOUT_FILENO);
        }
        data->last_status = command_exec(cmd->args, data);
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
        if (fd_in != -1) close(fd_in);
        if (fd_out != -1) close(fd_out);
    }
    else
    {
        cmd->pid = fork();
        if (cmd->pid == -1)
        {
            error_msg(FORK_ERROR);
            return;
        }
        if (cmd->pid)
            waitpid(cmd->pid, &data->last_status, 0);
        else
        {
            if (cmd->file_in)
            {
                fd_in = open(cmd->file_in, O_RDONLY);
                if (fd_in < 0)
                    exit(error_msg_arg(NO_PATH, cmd->file_in));
                if (dup2(fd_in, STDIN_FILENO) < 0)
                    exit(error_msg(DUP2_ERROR));
                close(fd_in);
            }
            if (cmd->file_out)
            {
                if (cmd->append_out)
                    fd_out = open(cmd->file_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
                else
                    fd_out = open(cmd->file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd_out < 0)
                    exit(error_msg_arg(NO_PATH, cmd->file_out));
                if (dup2(fd_out, STDOUT_FILENO) < 0)
                    exit(error_msg(DUP2_ERROR));
                close(fd_out);
            }
            char **envp = shell_envp_to_array(data->shell_envp);
            execve(cmd->args[0], cmd->args, envp);
            free_array(envp);
            free_cmd_list(data->first_cmd);
            free_data(data);
            exit(EXIT_SUCCESS);
        }
    }
}
