/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:15:14 by axlee             #+#    #+#             */
/*   Updated: 2024/05/31 15:46:39 by gyong-si         ###   ########.fr       */
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

void execute_builtins(t_token *curr, t_shell *minishell)
{
    int pid;

    if (ft_strncmp(curr->token, "exit", 4) == 0 ||
        ft_strncmp(curr->token, "export", 6) == 0 ||
        ft_strncmp(curr->token, "unset", 5) == 0)
    {
        execute_builtin_2(curr, minishell); // Only call execute_builtin_2 for exit, export, unset
    }
    else
    {
        pid = fork();
        if (pid == 0)
        {
            if (ft_strncmp(curr->token, "cd", 2) == 0 ||
                ft_strncmp(curr->token, "echo", 4) == 0 ||
                ft_strncmp(curr->token, "env", 3) == 0)
            {
                execute_builtin_1(curr, minishell); // Only call execute_builtin_1 for cd, echo, env
            }
            other_cmds(curr, minishell);
            exit(0); // Ensure child process exits after execution
        }
        else
        {
            minishell->process_ids[minishell->process_count++] = pid;
        }
    }
}

static void	execute_builtins_or_exec(int	i, t_token *curr, t_shell *minishell)
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
/***
void pipex(t_shell *minishell)
{
    int i;
    t_token *curr;
    t_token *start_cmd;
    int token_count;

    i = 0;
    curr = minishell->cmd_list;
    while (curr != NULL)
    {
        token_count = count_tokens(minishell); // Count tokens at the start of command processing
        printf("Total tokens: %d\n", token_count); // Display the total number of tokens

        if (check_redirection_type(curr))
            curr = curr->next;
        else if (curr->type == T_IDENTIFIER)
        {
            start_cmd = curr; // Start of a new command
            while (curr->next && curr->next->type == T_IDENTIFIER)
            {
                curr = curr->next; // Move to the end of the command arguments
            }
            execute_builtins_or_exc(i++, start_cmd, minishell); // Execute the whole command with arguments
        }
        curr = curr->next;
    }
    wait_for_all_commands(minishell);
    restore_fds(minishell->input_fd, minishell->output_fd);
} **/

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
	int		saved_stdin;
	int		saved_stdout;
	int		i;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	printf("execute with redirection\n");
	head = minishell->cmd_list;
	curr = head;
	curr = move_lst_by_index(minishell, index);
	printf("curr node in ex curr: %s\n", curr->token);
	handle_redirection(minishell, curr);
	i = 0;
	if (head)
	{
		execute_builtins_or_exec(i, head, minishell);
	}
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

static int	num_of_arguments(t_shell *minishell)
{
	int		i;
	t_token *curr;

	i = -1;
	curr = minishell->cmd_list;
	while (curr)
	{
		if (curr->type == T_IDENTIFIER)
		{
			i++;
		}
		else
			return (i);
		curr = curr->next;
	}
	return (i);
}

void	execute_without_redirection(t_shell *minishell)
{
	int		i;
	int		num;
	t_token	*curr;

	i = 0;
	num = 0;
	curr = minishell->cmd_list;
	printf("execute without redirections\n");
	while (curr != NULL)
	{
		if (curr->type == T_IDENTIFIER)
		{
			if (ft_strcmp(curr->token, "echo") == 0)
			{
				num = num_of_arguments(minishell);
				printf("number of arguments %d\n", num);
			}
			execute_builtins_or_exec(i++, curr, minishell);
			while (num > 0)
			{
				curr = curr->next;
				num--;
			}
		}
		curr = curr->next;
	}
}

void	pipex(t_shell *minishell)
{
	int	index;
	int token_count;

	index = check_for_redirections(minishell);
	printf("index %d\n", index);
	token_count = count_tokens(minishell);
    printf("Total tokens: %d\n", token_count);
	// if index > 0 means redirection is found
	if (index > 0)
		execute_with_redirection(minishell, index);
	else
		execute_without_redirection(minishell);
	wait_for_all_commands(minishell);
	restore_fds(minishell->input_fd, minishell->output_fd);
}
