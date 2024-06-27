/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:15:14 by axlee             #+#    #+#             */
/*   Updated: 2024/06/27 23:19:13 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_redirection(t_shell *minishell, t_token *curr)
{
	int	result;

	result = 0;
	if (curr->type == T_LESSER_THAN || curr->type == T_LEFT_SHIFT)
	{
		result = redirect_input(minishell, curr);
		if (result == -1)
			return (-1);
		dup2(minishell->input_fd, STDIN_FILENO);
		safe_close(&minishell->input_fd);
	}
	else if (curr->type == T_GREATER_THAN || curr->type == T_RIGHT_SHIFT)
	{
		result = redirect_output(minishell, curr);
		if (result == -1)
			return (-1);
		dup2(minishell->output_fd, STDOUT_FILENO);
		safe_close(&minishell->output_fd);
	}
	return (1);
}

int	handle_redirection(t_shell *minishell, t_token *curr)
{
	int	result;

	while (curr && check_redirection_type(curr))
	{
		result = handle_single_redirection(minishell, curr);
		if (result == -1)
			return (-1);
		if (curr->next && curr->next->next)
			curr = curr->next->next;
		else
			break ;
	}
	return (1);
}

static int	wait_for_all_commands(t_shell *minishell)
{
	int	i;
	int	num_of_process;
	int	status;

	i = 0;
	num_of_process = minishell->process_count;
	while (i < num_of_process)
	{
		waitpid(minishell->process_ids[i], &status, 0);
		if (WIFEXITED(status))
			minishell->last_return = WEXITSTATUS(status);
		else
		{
			minishell->last_return = 1;
			minishell->end = TRUE;
		}
		i++;
	}
	signal(SIGINT, sigint_handler);
	return (1);
}

t_token	*handle_builtins(t_token *curr, t_shell *minishell)
{
	int	num;
	int	index;
	int	num_of_pipe;

	num = num_of_args(curr);
	index = check_for_redirections(curr);
	num_of_pipe = pipe_found(curr);
	if (num_of_pipe == 0 && (index == 0))
		execute_builtin_or_exec(curr, minishell);
	else if (num_of_pipe == 0 && (index > 0))
		execute_with_redirection(curr, minishell, index);
	else
		execute_pipeline(curr, minishell);
	if (minishell->redir_no > 0)
		num += minishell->redir_no * 2;
	curr = move_lst_by_index(curr, num);
	return (curr);
}

void	pipex(t_shell *minishell)
{
	t_token	*curr;

	curr = minishell->cmd_list;
	while (curr != NULL && !minishell->end)
	{
		if (!ft_strcmp(curr->token, ""))
		{
			curr = curr->next;
			continue ;
		}
		else if (curr->type == T_IDENTIFIER && (!curr->next)
			&& (!check_builtin(curr->token)))
			execute_single_command(curr, minishell);
		else if ((curr->type == T_IDENTIFIER) && (curr->next)
			&& (curr->next->type == T_PIPE))
			execute_pipeline(curr, minishell);
		else if (curr->type == T_IDENTIFIER
			&& (check_builtin(curr->token) == 1))
			curr = handle_builtins(curr, minishell);
		else if ((curr->type == T_IDENTIFIER) && (!check_builtin(curr->token))
			&& (curr->next) && (check_redirection_type(curr->next)))
			curr = execute_with_redir(curr, minishell);
		curr = curr->next;
	}
	wait_for_all_commands(minishell);
}
