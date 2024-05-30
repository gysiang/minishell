/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:15:14 by axlee             #+#    #+#             */
/*   Updated: 2024/05/30 16:44:25 by gyong-si         ###   ########.fr       */
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

int	handle_redirection(t_shell *minishell, t_token *curr)
{
	if (curr->next && (curr->next->type == T_LESSER_THAN
			|| curr->next->type == T_LEFT_SHIFT))
	{
		if (redirect_input(minishell, curr->next->next) != -1)
		{
			dup2(minishell->input_fd, STDIN_FILENO);
			close(minishell->input_fd);
			return (1);
		}
	}
	else if (curr->next && (curr->next->type == T_GREATER_THAN
			|| curr->next->type == T_RIGHT_SHIFT))
	{
		if (redirect_output(minishell, curr->next->next) != -1)
		{
			dup2(minishell->output_fd, STDOUT_FILENO);
			close(minishell->output_fd);
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

static void wait_for_all_commands(t_shell *minishell)
{
	int status;
	int i;
	int	num_of_process;

	i = 0;
	num_of_process = minishell->process_count;
	while (i < num_of_process)
	{
		printf("Waiting for process: %d\n", minishell->process_ids[i]);
		waitpid(minishell->process_ids[i], &status, 0);
		if (WIFEXITED(status))
			minishell->last_return = WEXITSTATUS(status);
		else
			minishell->last_return = 1;
		i++;
	}
	minishell->process_count = 0;
}

void	execute_builtins(t_token *curr, t_shell *minishell)
{
	int	pid;

	pid = fork();

	if (pid == 0)
	{
		execute_builtin_1(curr, minishell);
		execute_builtin_2(curr, minishell);
		other_cmds(curr, minishell);
	}
	else
	{
		minishell->process_ids[minishell->process_count++] = pid;
	}
}

static void	execute_builtins_or_exc(int	i, t_token *curr, t_shell *minishell)
{
	if (check_builtin(curr->token))
	{
		execute_builtins(curr, minishell);
	}
	else
		execute_command(i, curr, minishell);
}

void	restore_fds(int	input_fd, int output_fd)
{
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
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
			execute_builtins_or_exc(i++, curr, minishell);
			if (curr->next && curr->next->type == T_IDENTIFIER)
				curr = curr->next;
		}
		curr = curr->next;
	}
	wait_for_all_commands(minishell);
	restore_fds(minishell->input_fd, minishell->output_fd);
}
// need to rewrite pipex
/**
echo,
hello world
>>
output.txt

in echo i need to move the linked list till its a different type;
1. check if there is execute_builtins
2. echo Hello world > output.txt
**/
