/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:24:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/15 14:50:38 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/minishell.h"

/* Split the command string into parts based on spaces, then find the full path
of the command to be exxecuted. If the command fails to execute, will print the
eroor messages, free the allocated memmory and then exits the program */

void	exec_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	//printf("cmd: %s\n", cmd);
	if (!cmd || !env)
	{
		ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	s_cmd = ft_split(cmd, ' ');
	//for (int i = 0; s_cmd[i] != NULL; i++) {
	//	printf("s_cmd[%d]: %s\n", i, s_cmd[i]);
	//}
	if (!s_cmd)
	{
		ft_putstr_fd("Failed to split command\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	path = get_path(s_cmd[0], env);
	//printf("path: %s\n", path);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: Error executing command\n", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
}

/* Opens the file name given by the user, makes the program read from the
opened file and redirects the output of the file to the parents process.

Before running the command, will close any files and connections it does
not need anymore. */

/**
void	child(char **argv, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(argv[0], 0);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening input file\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Error Child dup2 input\n", STDERR_FILENO);
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error Child dup2 pipe\n", STDERR_FILENO);
		close(fd);
		close(p_fd[1]);
		exit(EXIT_FAILURE);
	}
	close(fd);
	close(p_fd[0]);
	//printf("child cmd: %s\n", argv[1]);
	exec_cmd(argv[1], env);
} **/

void child(char **argv, int *p_fd, char **env)
{
    if (dup2(p_fd[1], STDOUT_FILENO) == -1)
    {
        ft_putstr_fd("Error Child dup2 pipe\n", STDERR_FILENO);
        //exit(EXIT_FAILURE);
		return ;
    }
    close(p_fd[0]);
    close(p_fd[1]);
    exec_cmd(argv[0], env);
}


/* Setup a command to run with its output going to a file and input
coming from another command. Will try to open the output file before
getting the input from a pipe and finally the output goes to
the file we just opened.

After setting up input and output, it closes and files and connections
it doesnt need anymore and run the command. */

/***
void	parent(char **argv, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(argv[3], 1);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening output file\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Error Parent dup2 pipe\n", STDERR_FILENO);
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error Parent dup2 output\n", STDERR_FILENO);
		close(fd);
		close(p_fd[0]);
		exit(EXIT_FAILURE);
	}
	close(fd);
	close(p_fd[1]);
	//printf("parent cmd: %s\n", argv[1]);
	exec_cmd(argv[2], env);
} **/

void parent(char **argv, int *p_fd, char **env)
{
    if (dup2(p_fd[0], STDIN_FILENO) == -1)
    {
        ft_putstr_fd("Error Parent dup2 pipe\n", STDERR_FILENO);
        //exit(EXIT_FAILURE);
		return ;
    }
    close(p_fd[0]);
    close(p_fd[1]);
    exec_cmd(argv[1], env);
}
