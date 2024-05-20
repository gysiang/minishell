/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:01:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/20 13:21:49 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(int i, t_token *curr, t_shell *minishell, int last_command)
{
    int pipe_fd[2];
    int pid;
    int num_of_command;
    int status;

    num_of_command = num_of_commands(minishell);
    if (i != num_of_command - 1)
    {
        if (pipe(pipe_fd) == -1)
            exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == 0)
    {
        // Child process
        if (!last_command)
        {
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[0]);
        }
        if (handle_redirection(minishell, curr) != 1)
        {
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[1]);
        }
        exec_cmd(curr->token, minishell);
    }
    else
    {
        // Parent process
        if (last_command)
        {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
        }
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            minishell->last_return = WEXITSTATUS(status);
        }
        else
        {
            minishell->last_return = 1;
        }
    }
}

void exec_cmd(char *cmd, t_shell *minishell) {
    char **s_cmd;
    char *path;
    int return_code;

    if (!cmd || !minishell) {
        ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
        minishell->last_return = 1;
        return;
    }

    // Handle the special case for `$?`
    if (ft_strncmp(cmd, "$?", 2) == 0) {
        printf("%d\n", minishell->last_return); // Print last return status
        minishell->last_return = 0; // Reset last return status
        return;
    }

    s_cmd = ft_split(cmd, ' ');
    if (!s_cmd) {
        ft_putstr_fd("Failed to split command\n", STDERR_FILENO);
        minishell->last_return = 1;
        return;
    }

    // Assuming you have functions like execute_builtin_* and other_cmds
    if (execute_builtin_1(minishell) || execute_builtin_2(minishell) || other_cmds(minishell)) {
        ft_free_tab(s_cmd);
        return;
    }

    path = get_path(s_cmd[0], minishell);
    if (!path) {
        return_code = minishell_error_msg(s_cmd[0], 42); // 0 corresponds to "command not found"
        minishell->last_return = return_code;
        ft_free_tab(s_cmd);
        return;
    }

    if (execve(path, s_cmd, minishell->env) == -1) {
        return_code = minishell_error_msg(s_cmd[0], errno); // Use errno to get the specific error
        minishell->last_return = return_code;
        ft_free_tab(s_cmd);
        exit(return_code);
    }

    ft_free_tab(s_cmd);
}