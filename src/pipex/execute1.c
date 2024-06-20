/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:10:53 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/20 20:56:14 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_redir_token(t_token *curr, t_shell *minishell)
{
	t_token	*redir_token;

	redir_token = NULL;
	if (curr->next && curr->next->next
		&& check_redirection_type(curr->next->next->next))
	{
		minishell->flag = 1;
		redir_token = curr->next->next->next;
	}
	return (redir_token);
}

void	handle_redir_child_process(t_token *curr, t_shell *minishell,
		t_token *redir_token)
{
	signal(SIGINT, SIG_DFL);
	load_previous_fd_to_stdin(minishell);
	if (redir_token)
		handle_redirection(minishell, redir_token);
	if (handle_redirection(minishell, curr->next))
	{
		if (minishell->output_fd != -1)
		{
			dup2(minishell->output_fd, STDOUT_FILENO);
			close(minishell->output_fd);
		}
		exec_cmd(curr, minishell);
	}
}

void	handle_redir_parent_process(t_shell *minishell, int pid)
{
	signal(SIGINT, sigint_handler1);
	minishell->process_ids[minishell->process_count++] = pid;
	if (minishell->prev_fd != -1)
		close(minishell->prev_fd);
}

void	execute_command_with_redir(t_token *curr, t_shell *minishell)
{
	int			pid;
	int			pipe_fd[2];
	t_token		*redir_token;

	redir_token = get_redir_token(curr, minishell);
	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		handle_redir_child_process(curr, minishell, redir_token);
	else
	{
		handle_redir_parent_process(minishell, pid);
		//waitpid(pid, NULL, 0);
	}
}
