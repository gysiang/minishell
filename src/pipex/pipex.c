/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:15:14 by axlee             #+#    #+#             */
/*   Updated: 2024/06/20 12:58:45 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirection(t_shell *minishell, t_token *curr)
{
	if (curr && (curr->type == T_LESSER_THAN || curr->type == T_LEFT_SHIFT))
	{
		if (redirect_input(minishell, curr) != -1)
		{
			dup2(minishell->input_fd, STDIN_FILENO);
			close(minishell->input_fd);
			return (1);
		}
	}
	else if (curr && (curr->type == T_GREATER_THAN
			|| curr->type == T_RIGHT_SHIFT))
	{
		if (redirect_output(minishell, curr) != -1 && !minishell->flag)
		{
			dup2(minishell->output_fd, STDOUT_FILENO);
			close(minishell->output_fd);
			return (1);
		}
		else
			return (1);
	}
	return (0);
}

static int	wait_for_all_commands(t_shell *minishell)
{
	int	status;
	int	i;
	int	num_of_process;

	i = 0;
	num_of_process = minishell->process_count;
	while (i < num_of_process)
	{
		waitpid(minishell->process_ids[i], &status, 0);
		if (WIFEXITED(status))
			minishell->last_return = WEXITSTATUS(status);
		else
			minishell->last_return = 1;
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

	num = num_of_arguments(minishell);
	index = check_for_redirections(minishell);
	num_of_pipe = num_of_pipes(minishell);
	if (index > 0)
		num += 2;
	if (num_of_pipe == 0 && (index == 0))
	{
		execute_builtin_or_exec(curr, minishell);
	}
	else if (num_of_pipe == 0 && (index > 0))
		execute_with_redirection(curr, minishell,
			check_for_redirections(minishell));
	else
		execute_pipeline(curr, minishell);
	curr = move_lst_by_index(curr, num);
	return (curr);
}

void	pipex(t_shell *minishell)
{
	t_token	*curr;

	curr = minishell->cmd_list;
	while (curr != NULL)
	{
		if (curr->type == T_IDENTIFIER && (!curr->next)
			&& (!check_builtin(curr->token)))
			execute_single_command(curr, minishell);
		else if ((curr->type == T_IDENTIFIER) && (curr->next)
			&& (curr->next->type == T_PIPE))
			execute_pipeline(curr, minishell);
		else if (curr->type == T_IDENTIFIER && (check_builtin(curr->token) == 1))
			curr = handle_builtins(curr, minishell);
		else if ((curr->type == T_IDENTIFIER) && (!check_builtin(curr->token))
			&& (curr->next) && (check_redirection_type(curr->next)))
		{
			execute_command_with_redir(curr, minishell);
			update_curr_pointer(&curr, minishell->flag);
		}
		curr = curr->next;
	}
	wait_for_all_commands(minishell);
}

/*void	pipex(t_shell *minishell)
{
	t_token	*curr;

	curr = minishell->cmd_list;
	while (curr != NULL)
	{
		if (curr->type == T_IDENTIFIER && (!curr->next)
			&& (!check_builtin(curr->token)))
			execute_single_command(curr, minishell);
		if ((curr->type == T_IDENTIFIER) && (curr->next)
			&& (curr->next->type == T_PIPE))
			execute_pipeline(curr, minishell);
		if (curr->type == T_IDENTIFIER && (check_builtin(curr->token) == 1))
			curr = handle_builtins(curr, minishell);
		if ((curr->type == T_IDENTIFIER) && (!check_builtin(curr->token))
			&& (curr->next) && (check_redirection_type(curr->next)))
		{
			execute_command_with_redir(curr, minishell);
			update_curr_pointer(&curr, minishell->flag);
		}
		curr = curr->next;
	}
	wait_for_all_commands(minishell);
}*/



