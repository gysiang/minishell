/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:24:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/06 18:02:11 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Split the command string into parts based on spaces, then find the full path
of the command to be exxecuted. If the command fails to execute, will print the
eroor messages, free the allocated memmory and then exits the program */

int are_fds_closed(int *fds, int num_fds) {
    for (int i = 0; i < num_fds; i++) {
        if (fcntl(fds[i], F_GETFD) != -1 || errno != EBADF) {
            // File descriptor is still open
            return 0; // Return false
        }
    }
    return 1; // All file descriptors are closed, return true
}
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

void	pipex(t_shell *minishell)
{
	int		i;
	int		num_of_command;
	char	**command;
	//int		p_fd[2];
	int		pid;
	pid_t	*child_pids;

	num_of_command = num_of_commands(minishell);
	command = init_command(minishell->cmd_list, num_of_command);
	child_pids = malloc(num_of_command * sizeof(*child_pids));
	if (!child_pids)
		return ;
	i = 0;
	while (i < num_of_command)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (!pid)
		{
			child(minishell, command[i]);
		}
		else
			waitpid(pid, NULL, 0);
		i++;
	}
	// wait for all the child process to finish executing
	//for (int i = 0; i < num_of_command; i++) {
    //    printf("Child %d PID: %d\n", i + 1, child_pids[i]);
    //}
	if (num_of_command == 1)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (!pid)
			exec_cmd(command[num_of_command - 1], minishell);
		else
			waitpid(pid, NULL, 0);
	}
	free(command);
	free(child_pids);
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
/***
void	do_pipe(char *command, t_shell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		child(p_fd, minishell, command);
	else
		parent(p_fd, minishell, command);
} **/
