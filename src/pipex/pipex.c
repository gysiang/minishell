/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:24:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/06 09:57:52 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Split the command string into parts based on spaces, then find the full path
of the command to be exxecuted. If the command fails to execute, will print the
eroor messages, free the allocated memmory and then exits the program */

static char	**init_command(t_token *token_lst, int num_of_command)
{
	t_token	*curr_token;
	char	**command;
	int		i;

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

void	pipex(t_token *token_lst, t_shell *minishell)
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
	i = 0;
	while (i < num_of_command - 1)
	{
		do_pipe(command[i++], minishell);
	}
	exec_cmd(command[num_of_command - 1], minishell);
	ft_free_tab(command);
}

void	exec_cmd(char *cmd, t_shell *minishell)
{
	char	**s_cmd;
	char	*path;

	if (!cmd || !minishell) {
		ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd) {
		ft_putstr_fd("Failed to split command\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	path = get_path(s_cmd[0], minishell->env);
	if (!path) {
		printf("get_env returned NULL for command: %s\n", s_cmd[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(path, s_cmd, minishell->env) == -1) {
		ft_putstr_fd("pipex: Error executing command\n", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
}

void	child(int *p_fd, t_shell *minishell, char *command)
{
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error Child dup2 pipe\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	printf("child command %s\n", command);
	exec_cmd(command, minishell);
}

void	parent(int *p_fd, t_shell *minishell, char *command)
{
	(void)minishell;
	(void)command;
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Error Parent dup2 pipe\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	//printf("parent command %s\n", command);
	//exec_cmd(command, minishell);
}

void	do_pipe(char *command, t_shell *minishell)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		child(p_fd, minishell, command);
	else
		parent(p_fd, minishell, command);
}
