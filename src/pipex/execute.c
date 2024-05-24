/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:59:21 by axlee             #+#    #+#             */
/*   Updated: 2024/05/24 16:14:11 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(int i, t_token *curr, t_shell *minishell)
{
	int pipe_fd[2];
	int pid;
	int	num_of_pipe = num_of_pipes(minishell);

	if (i <= num_of_pipe - 1)
	{
		if (pipe(pipe_fd) == -1)
			exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		if (!handle_redirection(minishell, curr))
		{
			if (minishell->prev_fd != -1)
			{
				dup2(minishell->prev_fd, STDIN_FILENO);
				close(minishell->prev_fd);
			}
			if (i < num_of_pipe)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
                close(pipe_fd[0]);
			}
		}
        exec_cmd(curr->token, minishell);
	}
	else
	{
		if (minishell->prev_fd != -1)
			close(minishell->prev_fd);
		if (i < num_of_pipe)
		{
			minishell->prev_fd = pipe_fd[0];
            close(pipe_fd[1]);
		}
    }
}

void exec_cmd(char *cmd, t_shell *minishell)
{
    char **s_cmd;
    char *path;
    int return_code;

    printf("Executing command: %s\n", cmd);

    if (!cmd || !minishell) {
        printf("Invalid command or shell context\n");
        ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
        minishell->last_return = 1;
        return;
    }

    if (ft_strncmp(cmd, "$?", 2) == 0) {
        printf("Handling special case for last return status\n");
        printf("%d\n", minishell->last_return);
        minishell->last_return = 0;
        return;
    }

    s_cmd = ft_split(cmd, ' ');
    if (!s_cmd) {
        printf("Failed to split command string\n");
        ft_putstr_fd("Failed to split command\n", STDERR_FILENO);
        minishell->last_return = 1;
        return;
    }

    if (execute_builtin_1(minishell) || execute_builtin_2(minishell) || other_cmds(minishell)) {
        printf("Executed a builtin or other command\n");
        ft_free_tab(s_cmd);
        return;
    }

    path = get_path(s_cmd[0], minishell);
    if (!path) {
        printf("Command not found: %s\n", s_cmd[0]);
        return_code = minishell_error_msg(s_cmd[0], 42);
        minishell->last_return = return_code;
        ft_free_tab(s_cmd);
        return;
    }

    printf("Executing external command via execve: %s\n", path);
    if (execve(path, s_cmd, minishell->env) == -1) {
        printf("execve failed: %s\n", strerror(errno));
        return_code = minishell_error_msg(s_cmd[0], errno);
        minishell->last_return = return_code;
        ft_free_tab(s_cmd);
        exit(return_code);
    }

    ft_free_tab(s_cmd);
}
