/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:30:03 by axlee             #+#    #+#             */
/*   Updated: 2024/07/02 22:24:09 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_child_process(int *pipe_fd, t_shell *minishell)
{
	signal(SIGPIPE, SIG_IGN);
	load_previous_fd_to_stdin(minishell);
	dup2(pipe_fd[1], STDOUT_FILENO);
	safe_close(&pipe_fd[1]);
	safe_close(&pipe_fd[0]);
}

void	handle_redirections(t_token *curr, t_shell *minishell)
{
	t_token	*redir;

	redir = curr;
	while (redir && redir->type != T_PIPE)
	{
		if (check_redirection_type(redir))
			handle_redirection(minishell, redir);
		redir = redir->next;
	}
}

void	child_process(t_token *curr, int *pipe_fd, t_shell *minishell)
{
	setup_child_process(pipe_fd, minishell);
	handle_redirections(curr, minishell);
	execute_builtin_or_exec_exit(curr, minishell);
}

void	parent_process(int pid, int *pipe_fd, t_shell *minishell)
{
	minishell->process_ids[minishell->process_count++] = pid;
	if (minishell->prev_fd != -1)
		safe_close(&minishell->prev_fd);
	minishell->prev_fd = pipe_fd[0];
	safe_close(&pipe_fd[1]);
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
		load_previous_fd_to_stdin(minishell);
		dup2(pipe_fd[1], STDOUT_FILENO);
		safe_close(&pipe_fd[1]);
		safe_close(&pipe_fd[0]);
		handle_redirections(curr, minishell);
		execute_builtin_or_exec_exit(curr, minishell);
	}
	else
	{
		minishell->process_ids[minishell->process_count++] = pid;
		if (minishell->prev_fd != -1)
			safe_close(&minishell->prev_fd);
		minishell->prev_fd = pipe_fd[0];
		safe_close(&pipe_fd[1]);
	}
}
