/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:24:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/23 15:42:04 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

/* Split the command string into parts based on spaces, then find the full path
of the command to be exxecuted. If the command fails to execute, will print the
eroor messages, free the allocated memmory and then exits the program */

//for (int i = 0; s_cmd[i] != NULL; i++) {
//	printf("s_cmd[%d]: %s\n", i, s_cmd[i]);
//}

void	exec_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (!cmd || !env)
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
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: Error executing command\n", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
}

void child(char *command, int *p_fd, char **env)
{
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error Child dup2 pipe\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	exec_cmd(command, env);
}

void parent(int *p_fd)
{
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Error Parent dup2 pipe\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	//exec_cmd(command, env);
}

void	do_pipe(char *command, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		child(command, p_fd, env);
	else
		parent(p_fd);
}
