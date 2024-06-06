/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:59:21 by axlee             #+#    #+#             */
/*   Updated: 2024/06/06 11:12:10 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_command(t_token *curr, t_shell *minishell)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		load_previous_fd(minishell);
		exec_cmd(curr, minishell);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		minishell->process_ids[minishell->process_count++] = pid;
		if (minishell->prev_fd != -1)
			close(minishell->prev_fd);
	}
}

void	execute_builtin_or_exec_exit(t_token *curr, t_shell *minishell)
{
	if (check_builtin(curr->token))
	{
		execute_builtin_1(curr, minishell);
		execute_builtin_2(curr, minishell);
		other_cmds(curr, minishell);
		exit(0);
	}
	else
		exec_cmd(curr, minishell);
}

void	execute_builtin_or_exec(t_token *curr, t_shell *minishell)
{
	int	builtin_type ;

	builtin_type = check_builtin(curr->token);
	if (builtin_type == 1)
	{
		execute_builtin_1(curr, minishell);
		execute_builtin_2(curr, minishell);
		other_cmds(curr, minishell);
	}
	else
		execute_single_command(curr, minishell);
}

void	execute_pipeline(t_token *curr, t_shell *minishell)
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		load_previous_fd(minishell);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		execute_builtin_or_exec_exit(curr, minishell);
	}
	else
	{
		minishell->process_ids[minishell->process_count++] = pid;
		if (minishell->prev_fd != -1)
			close(minishell->prev_fd);
		minishell->prev_fd = pipe_fd[0];
		close(pipe_fd[1]);
	}
}

void	execute_with_redirection(t_token *token, t_shell *minishell, int index)
{
	t_token	*head;
	t_token	*curr;
	int		saved_stdin;
	int		saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	printf("execute with redirection\n");
	if (!ft_strncmp(minishell->cmd_list->token, "echo", 4))
		head = minishell->cmd_list;
	else
		head = token;
	curr = head;
	curr = move_lst_by_index(curr, index);
	if (handle_redirection(minishell, curr))
	{
		execute_builtin_or_exec(head, minishell);
	}
	restore_fds(saved_stdin, saved_stdout);
}
