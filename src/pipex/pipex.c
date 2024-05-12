
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

/* Split the command string into parts based on spaces, then find the full path
of the command to be exxecuted. If the command fails to execute, will print the
eroor messages, free the allocated memmory and then exits the program */
/**
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
			//printf("command[%d]: %s\n", i, curr_token->token);
		}
		curr_token = curr_token->next;
	}
	command[num_of_command] = NULL;
	return (command);
} **/
/***
void	child_process(char *command, t_shell *minishell, int *fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec_cmd(command, minishell);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &status, 0);
	}
}

void	last_child_process(char *command, t_shell *minishell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (!pid)
		exec_cmd(command, minishell);
	else
	{
		waitpid(pid, &status, 0);
	}
} **/

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

void	wait_for_children(pid_t *child_pids, int num_of_command)
{
	int	i;

	i = 0;
	while (num_of_command > i)
	{
		waitpid(child_pids[i], NULL, 0);
		i++;
	}
}

void	child(int *curr_pipe, int i, int num_of_command)
{
	if (i != 0)
	{
		dup2(curr_pipe[0], STDIN_FILENO);
		close(curr_pipe[0]);
		close(curr_pipe[1]);
	}
	if (i != num_of_command - 1)
	{
		dup2(curr_pipe[1], STDOUT_FILENO);
		close(curr_pipe[0]);
		close(curr_pipe[1]);
	}
}

void	parent(int *curr_pipe, int i)
{
	if (i != 0)
	{
		close(curr_pipe[0]);
		close(curr_pipe[1]);
	}
}

void	execute_command(int i, char *command, t_shell *minishell, int last_command)
{
	int	pipe_fd[2];
	int pid;
	int status;

	int num_of_command = num_of_commands(minishell);
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
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[1]);
		}
		exec_cmd(command, minishell);
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
/***
void	do_pipe(int i, pid_t *child_pids, char *command, t_shell *minishell)
{
	int		num_of_command;
	pid_t	pid;

	num_of_command = num_of_commands(minishell);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		child(minishell->data_fd, i, num_of_command);
		exec_cmd(command, minishell);
	}
	else
	{
		child_pids[i] = pid;
		parent(minishell->data_fd, i, num_of_command);
	}
} **/

void pipex(t_shell *minishell)
{
	int		i;
	int		fd[2];
	//int		pid;
	pid_t	*child_pids;
	t_token	*curr;
	//int p_fd;
	int is_last_command = 0;
	i = 0;
	if (pipe(fd) == -1)
		return ;
	child_pids = (pid_t *)malloc(sizeof(pid_t) * num_of_commands(minishell));
	if (child_pids == NULL)
		exit(EXIT_FAILURE);
	curr = minishell->cmd_list;
	while (curr != NULL)
	{
		/***
		if (curr->type == T_LEFT_SHIFT)
		{
			p_fd = here_doc(minishell, curr->next->token);
			dup2(p_fd, STDIN_FILENO);
			close(p_fd);
			curr = curr->next->next;
		}
		else if (curr->type == T_LESSER_THAN)
		{
			p_fd = redirect_input(minishell, curr);
			pid = fork();
			if (!pid)
			{
				if (dup2(p_fd, STDIN_FILENO) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
				close(p_fd);
				exec_cmd(curr->prev->token, minishell);
			}
			waitpid(pid, NULL, 0);
			curr = curr->next;
		}
		else if (curr->type == T_GREATER_THAN || curr->type == T_RIGHT_SHIFT)
			redirect_output(curr);
		**/
		if (curr->type == T_IDENTIFIER)
		{
			//do_pipe(i++, child_pids, curr->token, minishell);
			is_last_command = (curr->next == NULL);
			//printf("Executing command: %s, Last command: %d\n", curr->token, is_last_command);
			execute_command(i++, curr->token, minishell, is_last_command);
		}
		curr = curr->next;
	}
	wait_for_children(child_pids, i);
	free(child_pids);
}

void	exec_cmd(char *cmd, t_shell *minishell)
{
	char	**s_cmd;
	char	*path;

	printf("cmd: %s\n", cmd);
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
