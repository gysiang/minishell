/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:15:14 by axlee             #+#    #+#             */
/*   Updated: 2024/05/17 16:27:55 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_process(int pipe_fd[2], t_token *curr, t_shell *minishell,
		int last_command)
{
	if (!last_command)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
	}
	if (handle_redirection(minishell, curr) != 1)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
	}
	exec_cmd(curr->token, minishell);
	exit(EXIT_FAILURE);
}

void	handle_parent_process(int pipe_fd[2], int pid, int last_command)
{
	int	status;

	if (last_command)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	waitpid(pid, &status, 0);
}

void	execute_command(int i, t_token *curr, t_shell *minishell,
		int last_command)
{
	int	pipe_fd[2];
	int	pid;
	int	num_of_command;

	num_of_command = num_of_commands(minishell);
	if (i != num_of_command - 1)
	{
		if (pipe(pipe_fd) == -1)
			exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		handle_child_process(pipe_fd, curr, minishell, last_command);
	else
		handle_parent_process(pipe_fd, pid, last_command);
}

char	**prepare_command(char *cmd, t_shell *minishell)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
	{
		ft_putstr_fd("Failed to split command\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	path = get_path(s_cmd[0], minishell);
	if (!path)
	{
		printf("get_env returned NULL for command: %s\n", s_cmd[0]);
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
	s_cmd[0] = path;
	return (s_cmd);
}

void	exec_cmd(char *cmd, t_shell *minishell)
{
	char	**s_cmd;

	if (!cmd || !minishell)
	{
		ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	s_cmd = prepare_command(cmd, minishell);
	if (execute_builtin_1(minishell) || execute_builtin_2(minishell) || other_cmds(minishell))
	{
		ft_free_tab(s_cmd);
		return ;
	}
	if (execve(s_cmd[0], s_cmd, minishell->env) == -1)
	{
		ft_putstr_fd("pipex: Error executing command\n", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
	ft_free_tab(s_cmd);
}
