/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:24:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/29 23:24:39 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Split the command string into parts based on spaces, then find the full path
of the command to be exxecuted. If the command fails to execute, will print the
eroor messages, free the allocated memmory and then exits the program */

//for (int i = 0; s_cmd[i] != NULL; i++) {
//	printf("s_cmd[%d]: %s\n", i, s_cmd[i]);
//}

/***
void	pipex(char *input, char **env)
{
	int		n;
	int		i;
	char	**command;

	command = ft_dqsplit(input, ' ');
	convert_cmd(command);
	i = 0;
	n = 0;
	while (command[n] != NULL)
		n++;
	while (i < n - 1)
	{
		do_pipe(command[i++], env);
	}
	exec_cmd(command[i], env);
} **/

static char	**init_command(t_token *token_lst, int num_of_command)
{
	t_token	*curr_token;
	char	**command;
	int	i;

	command = (char **)malloc((num_of_command + 1) * sizeof(char *));
	if (!command)
		exit(EXIT_FAILURE);
	i = 0;
	curr_token = token_lst;
	while (i < num_of_command)
	{
		if (curr_token->type == T_IDENTIFIER)
		{
			command[i++] = curr_token->token;
		 	printf("command[%d]: %s\n", i, curr_token->token);
		}
		curr_token = curr_token->next;
	}
	command[num_of_command] = NULL;
	return (command);
}

void	pipex(t_token *token_lst, char **env)
{
	int		i;
	int		num_of_command;
	t_token	*curr_token;
	char	**command;

	curr_token = token_lst;
	num_of_command = 0;
	while (curr_token != NULL)
	{
		if (curr_token->type == T_IDENTIFIER)
			num_of_command++;
		curr_token = curr_token->next;
	}
	command = init_command(token_lst, num_of_command);
	/***
	for (int i = 0; command[i] != NULL; i++) {
		printf("p_command[%d]: %s\n", i, command[i]);
	} **/
	i = 0;
	while (i < num_of_command - 1)
	{
		do_pipe(command[i++], env);
	}
	exec_cmd(command[num_of_command - 1], env);
	free(command);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (!cmd || !env)
	{
		ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	//printf("exec_cmd is called\n");
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
	{
		ft_putstr_fd("Failed to split command\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	path = get_path(cmd, env);
	//printf("path: %s\n", path);
	if (!path) {
		printf("get_path returned NULL\n");
		exit(EXIT_FAILURE);
	}
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
	printf("child command%s\n",command);
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
