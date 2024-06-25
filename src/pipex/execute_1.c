/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:59:21 by axlee             #+#    #+#             */
/*   Updated: 2024/06/25 16:41:34 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_numeric_command(t_token *curr, t_shell *minishell)
{
	if (curr->token && ft_isnumeric(curr->token))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(curr->token, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		minishell->last_return = 127;
		return (1);
	}
	return (0);
}
void execute_single_command(t_token *curr, t_shell *minishell)
{
    int pid;

    if (handle_numeric_command(curr, minishell))
        return;
    pid = fork();
    if (!ft_strcmp(curr->token, "./minishell"))
        minishell->signal_received = 1;
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        load_previous_fd_to_stdin(minishell);
        if (handle_redirection(minishell, curr->next) == -1)
            exit(1);
        exec_cmd(curr, minishell);
    }
    else
    {
        if (minishell->signal_received == 1)
            signal(SIGINT, SIG_IGN);
        else
            signal(SIGINT, sigint_handler1);
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
	int	builtin_type;

	if (minishell->prev_fd != 1)
		close(minishell->prev_fd);
	builtin_type = check_builtin(curr->token);
	if (builtin_type == 1)
	{
		execute_builtin_1(curr, minishell);
		execute_builtin_2(curr, minishell);
		other_cmds(curr, minishell);
	}
}

void	execute_pipeline(t_token *curr, t_shell *minishell)
{
	int		pipe_fd[2];
	int		pid;
	t_token	*redir;

	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		load_previous_fd_to_stdin(minishell);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		redir = curr;
		while (redir && redir->type != T_PIPE)
		{
			if (check_redirection_type(redir))
				handle_redirection(minishell, redir);
			redir = redir->next;
		}
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
	pid_t	pid;

	head = token;
	curr = head;
	curr = move_lst_by_index(curr, index);
	pid = fork();
	if (pid == 0)
	{
		while (curr != NULL && curr->next != NULL && check_redirection_type(curr))
		{
			minishell->redir_no += 1;
			handle_redirection(minishell, curr);
			if (curr->next->next != NULL)
				curr = curr->next->next;
			else
				break ;
		}
		execute_builtin_or_exec_exit(head, minishell);
	}
	else
	{
		minishell->process_ids[minishell->process_count++] = pid;
		if (minishell->prev_fd != -1)
			close(minishell->prev_fd);
	}
}
