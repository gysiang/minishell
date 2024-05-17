
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:24:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/07 21:15:41 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// WRITE A FUNCTION THAT IGNORES THE PARENT PROCESS SIGNAL WHEN WE FORK IT, BY RESETTING THE CHILD PROCESS SIGNAL TO 0 AND IGNORE PARENT. AFTER FINISH, ENABLE PARENT PROCESS SIGNAL AGAIN

#include "minishell.h"

static int	num_of_commands(t_shell *minishell)
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

static int	assign_last(t_token *c)
{
	if (c->next != NULL)
		return (0);
	else
		return (1);
}


static int	handle_redirection(t_shell *minishell, t_token *curr)
{
	if (curr->next && (curr->next->type == T_LESSER_THAN || curr->next->type == T_LEFT_SHIFT))
	{
		if (redirect_input(minishell,curr->next->next) != -1)
		{
			dup2(minishell->heredoc_fd, STDIN_FILENO);
			close(minishell->heredoc_fd);
			return (1);
		}
	}
	else if (curr->next && (curr->next->type == T_GREATER_THAN || curr->next->type == T_RIGHT_SHIFT))
	{
		if (redirect_output(minishell,curr->next->next) != -1)
		{
			dup2(minishell->heredoc_fd, STDOUT_FILENO);
			close(minishell->heredoc_fd);
			return (1);
		}
	}
	return (0);
}

void	execute_command(int i, t_token *curr, t_shell *minishell, int last_command)
{
	int	pipe_fd[2];
	int pid;
	int num_of_command;
	int status;

	//printf("executing %s\n", curr->token);
	num_of_command = num_of_commands(minishell);
	if (i != num_of_command - 1)
	{
		if (pipe(pipe_fd) == -1)
			exit(EXIT_FAILURE);
	}
	pid = fork();
	if (!pid)
	{
		if (!last_command)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
		}
		else
		{
			if (handle_redirection(minishell, curr) != 1)
			{
				dup2(pipe_fd[0], STDIN_FILENO);
				close(pipe_fd[1]);
			}
		}
		exec_cmd(curr->token, minishell);
	}
	else
	{
		if (last_command)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		waitpid(pid, &status, 0);
	}
}

static	int	check_redirection_type(t_token *curr)
{
	if (!curr)
		return (0);
	if (curr->type == T_LEFT_SHIFT || curr->type == T_LESSER_THAN
		|| curr->type == T_GREATER_THAN || curr->type == T_RIGHT_SHIFT)
	{
		return (1);
	}
	return (0);
}

void pipex(t_shell *minishell)
{
	int		i;
	int		is_last_command;
	t_token	*curr;

	i = 0;
	is_last_command = 0;
	curr = minishell->cmd_list;
	while (curr != NULL)
	{
		//printf("curr token processing %s\n", curr->token);
		if (check_redirection_type(curr))
		{
			curr = curr->next;
		}
		else if (curr->type == T_IDENTIFIER)
		{
			is_last_command = assign_last(curr);
			if (curr->next && (check_redirection_type(curr->next)))
			{
				is_last_command = 1;
			}
			execute_command(i++, curr, minishell, is_last_command);
		}
		curr = curr->next;
	}
}

void	exec_cmd(char *cmd, t_shell *minishell)
{
	char	**s_cmd;
	char	*path;

	if (!cmd || !minishell)
	{
		ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
	{
		ft_putstr_fd("Failed to split command\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	path = get_path(s_cmd[0], minishell);
	if (execute_builtin(minishell))
	{
		ft_free_tab(s_cmd);
		return ;
	}
	if (!path)
	{
		printf("get_env returned NULL for command: %s\n", s_cmd[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(path, s_cmd, minishell->env) == -1)
	{
		ft_putstr_fd("pipex: Error executing command\n", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
}
