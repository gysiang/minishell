/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:10:53 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/23 15:44:21 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_redir_token(t_token *curr)
{
	t_token	*redir_token;

	redir_token = NULL;
	if (curr->next && curr->next->next
		&& check_redirection_type(curr->next->next->next))
	{
		redir_token = curr->next->next;
	}
	return (redir_token);
}
/** *
static int	check_redir_token(t_token *curr)
{
	int	i;

	i = 0;
	if (curr->next && curr->next->next
		&& check_redirection_type(curr->next->next->next))
		i = 1;
	return (i);
} **/

void	handle_redir_child_process(t_token *curr, t_shell *minishell)
{
	t_token *head;
	//t_token *redir;
	//t_token *redir1;

	head = curr;
	signal(SIGINT, SIG_DFL);
	load_previous_fd_to_stdin(minishell);
	/** *
	handle_redirection(minishell, curr->next);
	if (check_redir_token(curr))
	{
		minishell->flag = 1;
		curr = move_lst_by_index(curr, 2);
		handle_redirection(minishell, curr->next);
	} **/
	while (curr != NULL && curr->next != NULL
			&& check_redirection_type(curr->next))
	{
		minishell->redir_no += 1;
		handle_redirection(minishell, curr->next);
		if (curr->next->next != NULL)
			curr = curr->next->next;
		else
			break;
	}
	exec_cmd(head, minishell);
}

void	handle_redir_parent_process(t_shell *minishell, int pid)
{
	signal(SIGINT, sigint_handler1);
	minishell->process_ids[minishell->process_count++] = pid;
	if (minishell->prev_fd != -1)
		close(minishell->prev_fd);
}

t_token	*execute_with_redir(t_token *curr, t_shell *minishell)
{
	int	num_of_pipe;
	int	num_of_redir;
	int	i;

	num_of_pipe = num_of_pipes(minishell);
	num_of_redir = num_of_redirections(minishell);
	i = num_of_args_or_file(minishell);
	if (num_of_pipe == 0 && num_of_redir <= 3)
		execute_command_with_redir(curr, minishell);
	else
		execute_redir_with_pipe(curr, minishell);
	curr = update_curr_pointer(curr, minishell->redir_no, i);
	return (curr);
}

void	execute_redir_with_pipe(t_token *curr, t_shell *minishell)
{
	int	pid;
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		load_previous_fd_to_stdin(minishell);
		if (handle_redirection(minishell, curr->next) == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(1);
		}
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		exec_cmd(curr, minishell);
	}
	else
	{
		signal(SIGINT, sigint_handler1);
		minishell->process_ids[minishell->process_count++] = pid;
		if (minishell->prev_fd != -1)
			close(minishell->prev_fd);
		minishell->prev_fd = pipe_fd[0];
		close(pipe_fd[1]);
	}
}

void	execute_command_with_redir(t_token *curr, t_shell *minishell)
{
	int			pid;
	//t_token		*redir_token;

	//redir_token = get_redir_token(curr, minishell);
	//printf("execute_command_with_redir\n");
	pid = fork();
	if (!pid)
		handle_redir_child_process(curr, minishell);
	else
		handle_redir_parent_process(minishell, pid);
}