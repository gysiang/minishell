/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:50:26 by axlee             #+#    #+#             */
/*   Updated: 2024/06/28 23:47:45 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_child_for_redirection(int *pipe_fd, t_shell *minishell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
	load_previous_fd_to_stdin(minishell);
	dup2(pipe_fd[1], STDOUT_FILENO);
	safe_close(&pipe_fd[1]);
	safe_close(&pipe_fd[0]);
}

int	handle_child_redirection_process(t_token *curr, int *pipe_fd,
		t_shell *minishell)
{
	if (handle_redirection(minishell, curr->next) == -1)
	{
		safe_close(&pipe_fd[0]);
		safe_close(&pipe_fd[1]);
		return (-1);
	}
	dup2(pipe_fd[1], STDOUT_FILENO);
	safe_close(&pipe_fd[1]);
	return (0);
}

void	child_process_for_redirection(t_token *curr, int *pipe_fd,
		t_shell *minishell)
{
	setup_child_for_redirection(pipe_fd, minishell);
	//if (handle_child_redirection_process(curr, pipe_fd, minishell) == -1)
	//	exit(minishell->last_return);
	handle_redirections(curr, minishell);
	execute_builtin_or_exec_exit(curr, minishell);
}

void	parent_process_for_redirection(int pid, int *pipe_fd,
		t_shell *minishell)
{
	handle_redir_parent_process(minishell, pid);
	minishell->prev_fd = pipe_fd[0];
	safe_close(&pipe_fd[1]);
}

void	execute_redirection_with_pipe(t_token *curr, t_shell *minishell)
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		child_process_for_redirection(curr, pipe_fd, minishell);
	else
		parent_process_for_redirection(pid, pipe_fd, minishell);
}
