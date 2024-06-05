/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:59:21 by axlee             #+#    #+#             */
/*   Updated: 2024/06/06 00:46:17 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_previous_fd(t_shell *minishell)
{
	if (minishell->prev_fd != -1)
	{
		dup2(minishell->prev_fd, STDIN_FILENO);
		close(minishell->prev_fd);
	}
}

void	execute_single_command(t_token *curr, t_shell *minishell)
{
	int	pid;
	int	return_code;
	char	**s_cmd;
	char	*path;

	return_code = 0;
	path = NULL;
	s_cmd = NULL;
	if (!check_command(curr->token, minishell))
	{
		s_cmd = get_command_array(curr->token, minishell);
		path = get_command_path(s_cmd, minishell);
	}
	pid = fork();
	if (pid == 0)
	{
		load_previous_fd(minishell);
		printf("path: %s\n", path);
		printf("s_cmd: %s\n", s_cmd[0]);
		signal(SIGINT, sigint_handler1);
		if (execve(path, s_cmd, minishell->env) == -1)
		{
			printf("execve failed: %s\n", strerror(errno));
			return_code = minishell_error_msg(s_cmd[0], errno);
			minishell->last_return = return_code;
		}
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		minishell->process_ids[minishell->process_count++] = pid;
		if (minishell->prev_fd != -1)
			close(minishell->prev_fd);
		ft_free_tab(s_cmd);
	}
}

void	execute_pipeline(t_token *curr, t_shell *minishell)
{
	int	pipe_fd[2];
	int	pid;
	char	**s_cmd;
	char	*path;
	int	return_code;

	path = NULL;
	s_cmd = NULL;
	return_code = 0;
	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	if (!check_command(curr->token, minishell))
	{
		s_cmd = get_command_array(curr->token, minishell);
		path = get_command_path(s_cmd, minishell);
	}
	pid = fork();
	if (pid == 0)
	{
		load_previous_fd(minishell);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		if (check_builtin(curr->token))
		{
			execute_builtin_1(curr, minishell);
			execute_builtin_2(curr, minishell);
			other_cmds(curr, minishell);
			exit(0);
		}
		else
		{
			if (execve(path, s_cmd, minishell->env) == -1)
			{
				printf("execve failed: %s\n", strerror(errno));
				return_code = minishell_error_msg(s_cmd[0], errno);
				minishell->last_return = return_code;
			}
		}
	}
	else
	{
		minishell->process_ids[minishell->process_count++] = pid;
		if (minishell->prev_fd != -1)
			close(minishell->prev_fd);
		minishell->prev_fd = pipe_fd[0];
		close(pipe_fd[1]);
		ft_free_tab(s_cmd);
	}
}

void	execute_with_redirection(t_token *token, t_shell *minishell, int index)
{
	t_token	*head;
	t_token	*curr;
	int		saved_stdin;
	int		saved_stdout;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	printf("execute with redirection\n");
	if (!ft_strncmp(minishell->cmd_list->token, "echo", 4))
		head = minishell->cmd_list;
	else
		head = token;
	curr = head;
	curr = move_lst_by_index(curr, index);
	if (handle_redirection(minishell, curr))
	{
		execute_builtin_or_exec(head, minishell);
	}
	restore_fds(saved_stdin, saved_stdout);
}

int	check_command(char *cmd, t_shell *minishell)
{
	if (!cmd || !minishell)
	{
		printf("Invalid command or shell context\n");
		ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
		minishell->last_return = 1;
		return (1);
	}
	if (ft_strncmp(cmd, "$?", 2) == 0)
	{
		printf("Handling special case for last return status\n");
		printf("%d\n", minishell->last_return);
		minishell->last_return = 0;
		return (1);
	}
	return (0);
}

char	**get_command_array(char *cmd, t_shell *minishell)
{
	char **s_cmd;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
	{
		printf("Failed to split command string\n");
		ft_putstr_fd("Failed to split command\n", STDERR_FILENO);
		minishell->last_return = 1;
		return (NULL);
	}
	return (s_cmd);
}

char	*get_command_path(char **s_cmd, t_shell *minishell)
{
	int		return_code;
	char	*path;

	return_code = 0;
	if (s_cmd[0][0] == '/' || s_cmd[0][0] == '.')
		path = s_cmd[0];
	else
		path = get_path(s_cmd[0], minishell);
	if (!path)
	{
		printf("Command not found: %s\n", s_cmd[0]);
		return_code = minishell_error_msg(s_cmd[0], 42);
		minishell->last_return = return_code;
		return (NULL);
	}
	return (path);
}


	/***
	if (execve(path, s_cmd, minishell->env) == -1)
	{
		printf("execve failed: %s\n", strerror(errno));
		return_code = minishell_error_msg(s_cmd[0], errno);
		minishell->last_return = return_code;
	} **/
	//ft_free_tab(s_cmd);
	//exit(return_code);

/***
void execute_command(int i, t_token *curr, t_shell *minishell)
{
	int pipe_fd[2];
	int pid;
	int	num_of_pipe = num_of_pipes(minishell);

	if (i <= num_of_pipe - 1)
	{
		if (pipe(pipe_fd) == -1)
			exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{		if (curr->type == T_IDENTIFIER && (check_builtin(curr->token) == 1))
			curr = handle_builtins(curr, minishell);./
			if (minishell->prev_fd != -1)
			{
				dup2(minishell->prev_fd, STDIN_FILENO);
				close(minishell->prev_fd);
			}
			if (i < num_of_pipe)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
                close(pipe_fd[1]);
			}
        exec_cmd(curr->token, minishell);
	}
	else
	{
        minishell->process_ids[minishell->process_count++] = pid;
		if (minishell->prev_fd != -1)
			close(minishell->prev_fd);
		if (i < num_of_pipe)
		{
			minishell->prev_fd = pipe_fd[0];
            close(pipe_fd[1]); signal(SIGINT, sigint_handler);
**/
