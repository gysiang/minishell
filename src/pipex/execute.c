/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:01:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/17 14:22:59 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(int i, t_token *curr, t_shell *minishell, int last_command)
{
	int	pipe_fd[2];
	int pid;
	int num_of_command;
	int status;

	//printf("executing %s\n", curr->token);
	num_of_command = num_of_commands(minishell);
	if (i <= num_of_command - 1)
	{
		if (pipe(pipe_fd) == -1)
			exit(EXIT_FAILURE);
	}
	pid = fork();
	if (!pid)
	{
		if (handle_redirection(minishell, curr) != 1)
		{
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[1]);
		}
		else if (!last_command)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
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
