/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:59:21 by axlee             #+#    #+#             */
/*   Updated: 2024/06/26 19:46:21 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	execute_builtin_directly(t_token *curr, t_shell *minishell)
{
	execute_builtin_1(curr, minishell);
	execute_builtin_2(curr, minishell);
	other_cmds(curr, minishell);
}

static void	execute_builtin_in_child(t_token *curr, t_shell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execute_builtin_directly(curr, minishell);
		exit(minishell->last_return);
	}
	else if (pid > 0)
		minishell->process_ids[minishell->process_count++] = pid;
	else
	{
		perror("fork");
		minishell->last_return = 1;
	}
}

void	execute_builtin_or_exec(t_token *curr, t_shell *minishell)
{
	if (minishell->prev_fd != 1)
		close(minishell->prev_fd);
	if (check_builtin(curr->token))
	{
		if (ft_strcmp(curr->token, "exit") == 0)
			handle_exit_command(curr, minishell);
		else if (ft_strcmp(curr->token, "cd") == 0 || ft_strcmp(curr->token,
				"export") == 0 || ft_strcmp(curr->token, "unset") == 0)
			execute_builtin_directly(curr, minishell);
		else
			execute_builtin_in_child(curr, minishell);
	}
	else
		exec_cmd(curr, minishell);
}

void	execute_with_redirection(t_token *token, t_shell *minishell, int index)
{
	t_token	*head;
	t_token	*curr;
	pid_t	pid;

	head = token;
	curr = head;
	curr = move_lst_by_index(curr, index);
	get_no_of_redir(curr, minishell);
	pid = fork();
	if (pid == 0)
	{
		handle_redirection(minishell, curr);
		execute_builtin_or_exec_exit(head, minishell);
	}
	else
	{
		minishell->process_ids[minishell->process_count++] = pid;
		if (minishell->prev_fd != -1)
			close(minishell->prev_fd);
	}
}
