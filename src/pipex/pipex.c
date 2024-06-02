/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:15:14 by axlee             #+#    #+#             */
/*   Updated: 2024/06/02 21:06:00 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void execute_builtin_or_exec(t_token *curr, t_shell *minishell)
{
	int builtin_type ;

	builtin_type = check_builtin(curr->token);
	//printf("builtin type: %d\n", builtin_type);
	//printf("curr type in builtin: %s\n", curr->token);
	if (builtin_type == 1)
	{
		execute_builtin_1(curr, minishell);
		execute_builtin_2(curr, minishell);
		other_cmds(curr, minishell);
	}
	else
		execute_single_command(curr, minishell);
}

t_token	*handle_echo(t_token *curr, t_shell *minishell)
{
	int num;
	int	index;
	int	num_of_pipe;

	num = num_of_arguments(minishell);
	index = check_for_redirections(minishell);
	num_of_pipe = num_of_pipes(minishell);
	//printf("in handle echo args: %d\n", num);
	if (num_of_pipe == 0 && (index == 0))
	{
		execute_builtin_or_exec(curr, minishell);
	}
	else if (num_of_pipe == 0 && (index > 0))
		execute_with_redirection(curr, minishell, check_for_redirections(minishell));
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
		printf("current token in process: %s\n", curr->token);
		if (curr->type == T_IDENTIFIER && (!curr->next))
			execute_builtin_or_exec(curr, minishell);
		if ((curr->type == T_IDENTIFIER) && (curr->next) && (curr->next->type == T_PIPE))
			execute_pipeline(curr, minishell);
		if (curr->type == T_IDENTIFIER && (check_builtin(curr->token) == 1))
		{
			curr = handle_echo(curr, minishell);
		}
		if ((curr->type == T_IDENTIFIER) && (curr->next) && (check_redirection_type(curr->next)))
		{
			execute_with_redirection(curr, minishell, 1);
			curr = curr->next->next;
		}
		curr = curr->next;
	}
	wait_for_all_commands(minishell);
	//restore_fds(minishell->input_fd, minishell->output_fd);
}

/***
void execute_builtins(t_token *curr, t_shell *minishell)
{
    int pid;

    if (ft_strncmp(curr->token, "exit", 4) == 0 ||
        ft_strncmp(curr->token, "export", 6) == 0 ||
        ft_strncmp(curr->token, "unset", 5) == 0)
    {
        execute_builtin_2(curr, minishell);
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
                execute_builtin_1(curr, minishell);
            }
            other_cmds(curr, minishell);
            exit(0);
        }
        else
            minishell->process_ids[minishell->process_count++] = pid;
    }
} **/


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

/***

static void	execute_builtins_or_exec(int i, t_token *curr, t_shell *minishell)
{
	if (check_builtin(curr->token))
	{
		execute_builtins(curr, minishell);
	}
	else
		execute_command(i, curr, minishell);
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
	token_count = count_tokens(minishell);
	printf("Total tokens: %d\n", token_count);
	if (index > 0)
		execute_with_redirection(minishell, index);
	else
		execute_without_redirection(minishell);
	wait_for_all_commands(minishell);
	restore_fds(minishell->input_fd, minishell->output_fd);
} **/
