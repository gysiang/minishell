/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:15:14 by axlee             #+#    #+#             */
/*   Updated: 2024/05/31 13:26:04 by gyong-si         ###   ########.fr       */
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
} **/
int	handle_redirection(t_shell *minishell, t_token *curr)
{
	if (curr && (curr->type == T_LESSER_THAN
			|| curr->type == T_LEFT_SHIFT))
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
		if (redirect_output(minishell, curr) != -1)
		{
			dup2(minishell->output_fd, STDOUT_FILENO);
			close(minishell->output_fd);
			return (1);
		}
	}
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

/***
void	execute_builtins(t_token *curr, t_shell *minishell)
{
	int	pid;
	int	count;

	if (ft_strncmp(curr->token, "exit", 4) == 0)
	{
		count = count_tokens(minishell);
		if (count > 2)
		{
			minishell_error_msg("exit", 43);
			return ;
		}
		minishell_exit(minishell);
		return ;
	}
	else
	{
		pid = fork();

		if (pid == 0)
		{
			execute_builtin_1(curr, minishell);
			execute_builtin_2(curr, minishell);
			other_cmds(curr, minishell);
		}
		else
			minishell->process_ids[minishell->process_count++] = pid;
	}
} **/

static void	execute_builtins_or_exec(int i, t_token *curr, t_shell *minishell)
{
	if (check_builtin(curr->token))
	{
		execute_builtin_1(curr, minishell);
		execute_builtin_2(curr, minishell);
		other_cmds(curr, minishell);
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

static int	check_redirection_type(t_token *curr)
{
	if (!curr)
		return (0);
	if (curr->type == T_LEFT_SHIFT || curr->type == T_LESSER_THAN
		|| curr->type == T_GREATER_THAN || curr->type == T_RIGHT_SHIFT)
		return (1);
	return (0);
}

static int	check_for_redirections(t_shell *minishell)
{
	t_token	*curr;
	int	i;

	i = 0;
	curr = minishell->cmd_list;
	while (curr)
	{
		if (check_redirection_type(curr))
			return (i);
		curr = curr->next;
		i++;
	}
	return (0);
}

t_token	*move_lst_by_index(t_shell *minishell, int index)
{
	t_token *curr;

	curr = minishell->cmd_list;
	while (curr != NULL && index > 0)
	{
		curr = curr->next;
		index--;
	}
	return (curr);
}

void	execute_with_redirection(t_shell *minishell, int index)
{
	t_token *head;
	t_token *curr;
	int		saved_stdout;
	int		i;

	saved_stdout = dup(STDOUT_FILENO);
	printf("execute with redirection\n");
	head = minishell->cmd_list;
	curr = head;
	curr = move_lst_by_index(minishell, index);
	// move to the redirection symbol
	printf("curr node in ex curr: %s\n", curr->token);
	handle_redirection(minishell, curr);
	// execute the echo/command in the head node
	i = 0;
	if (head)
	{
		execute_builtins_or_exec(i, head, minishell);
	}
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

void	execute_without_redirection(t_shell *minishell)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = minishell->cmd_list;
	printf("execute without redirections\n");
	while (curr != NULL)
	{
		if (curr->type == T_IDENTIFIER)
		{
			execute_builtins_or_exec(i++, curr, minishell);
			if (curr->next && curr->next->type == T_IDENTIFIER)
				curr = curr->next;
		}
		curr = curr->next;
	}
}
/***
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
			execute_builtins_or_exec(i++, curr, minishell);
			if (curr->next && curr->next->type == T_IDENTIFIER)
				curr = curr->next;
		}
		curr = curr->next;
	}
	wait_for_all_commands(minishell);
	restore_fds(minishell->input_fd, minishell->output_fd);
}
**/
void	pipex(t_shell *minishell)
{
	int	index;

	index = check_for_redirections(minishell);
	printf("index %d\n", index);
	// if index > 0 means redirection is found
	if (index > 0)
		execute_with_redirection(minishell, index);
	else
		execute_without_redirection(minishell);
	wait_for_all_commands(minishell);
	restore_fds(minishell->input_fd, minishell->output_fd);
}
