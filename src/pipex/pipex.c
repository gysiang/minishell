/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:24:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/07 08:58:03 by gyong-si         ###   ########.fr       */
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

void pipex(t_shell *minishell)
{
	int i;
	int num_of_command;
	char **command;
	int pid;
	pid_t *child_pids;
	int prev_pipe[2];
	int curr_pipe[2];

	i = 0;
	num_of_command = num_of_commands(minishell);
	child_pids = (pid_t *)malloc(sizeof(pid_t) * num_of_command);
	if (child_pids == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	command = init_command(minishell->cmd_list, num_of_command);
	while (num_of_command > i)
	{
		if (i != 0)
		{
			prev_pipe[0] = curr_pipe[0];
			prev_pipe[1] = curr_pipe[1];
		}
		if (i != num_of_command - 1)
		{
			if (pipe(curr_pipe) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
				}
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (!pid)
			{
				if (i != 0)
				{
					dup2(prev_pipe[0], STDIN_FILENO);
					close(prev_pipe[0]);
					close(prev_pipe[1]);
				}

				if (i != num_of_command - 1)
				{
					dup2(curr_pipe[1], STDOUT_FILENO);
					close(curr_pipe[0]);
					close(curr_pipe[1]);
				}
				exec_cmd(command[i], minishell);
			}
			else
			{
				child_pids[i] = pid;
				if (i != 0)
				{
					close(prev_pipe[0]);
					close(prev_pipe[1]);
				}
			}
			i++;
	}
	i = 0;
	while (i < num_of_command)
	{
		waitpid(child_pids[i], NULL, 0);
		i++;
	}
	free(command);
	free(child_pids)
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
	path = get_path(s_cmd[0], minishell);
	if (!path) {
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

void	child(t_shell *minishell, char *command)
{
	int		p_fd[2];

	printf("executing child process\n");
	if (pipe(p_fd) == -1)
	{
		printf("pipe failed\n");
		exit(EXIT_FAILURE);
	}
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
	{
		printf("dup failed\n");
		exit(EXIT_FAILURE);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	exec_cmd(command, minishell);
}

/**
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
} **/
