/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:15:14 by axlee             #+#    #+#             */
/*   Updated: 2024/05/24 16:16:34 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_of_commands(t_shell *minishell)
{
	int		i;
	t_token	*curr_token;

	i = 0;
	curr_token = minishell->cmd_list;
	i = 0;
	while (curr_token != NULL)
	{
		if (curr_token->type == T_IDENTIFIER)
			i++;
		curr_token = curr_token->next;
	}
	return (i);
}

int	num_of_pipes(t_shell *minishell)
{
	int		i;
	t_token	*curr_token;

	i = 0;
	curr_token = minishell->cmd_list;
	i = 0;
	while (curr_token != NULL)
	{
		if (curr_token->type == T_PIPE)
			i++;
		curr_token = curr_token->next;
	}
	return (i);
}
/***
static int	assign_last(t_token *c)
{
	if (c->next != NULL)
		return (0);
	else
		return (1);
} **/

int	handle_redirection(t_shell *minishell, t_token *curr)
{
	if (curr->next && (curr->next->type == T_LESSER_THAN
			|| curr->next->type == T_LEFT_SHIFT))
	{
		if (redirect_input(minishell, curr->next->next) != -1)
		{
			dup2(minishell->heredoc_fd, STDIN_FILENO);
			close(minishell->heredoc_fd);
			return (1);
		}
	}
	else if (curr->next && (curr->next->type == T_GREATER_THAN
			|| curr->next->type == T_RIGHT_SHIFT))
	{
		if (redirect_output(minishell, curr->next->next) != -1)
		{
			dup2(minishell->heredoc_fd, STDOUT_FILENO);
			close(minishell->heredoc_fd);
			return (1);
		}
	}
	return (0);
}

static int	check_redirection_type(t_token *curr)
{
	if (!curr)
		return (0);
	if (curr->type == T_LEFT_SHIFT || curr->type == T_LESSER_THAN
		|| curr->type == T_GREATER_THAN || curr->type == T_RIGHT_SHIFT)
		return (1);
	return (0);
}

static void wait_for_all_commands(t_shell *minishell, int num_of_pipe)
{
	int status;
	int i;

	i = 0;
	while (i++ < num_of_pipe + 1)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			minishell->last_return = WEXITSTATUS(status);
		else
			minishell->last_return = 1;
	}
}

void	pipex(t_shell *minishell)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = minishell->cmd_list;
	while (curr != NULL)
	{
		if (check_redirection_type(curr))
			curr = curr->next;
		else if (curr->type == T_IDENTIFIER)
		{
			execute_command(i++, curr, minishell);
		}
		curr = curr->next;
	}
	wait_for_all_commands(minishell, num_of_pipes(minishell));
}
