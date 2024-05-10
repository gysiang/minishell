
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
		//close(curr_pipe[1]);
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

void	do_pipe(int i, pid_t *child_pids, char *command, t_shell *minishell)
{
	int		curr_pipe[2];
	int		num_of_command;
	pid_t	pid;

	//printf("entered do pipe :%s\n", command);
	num_of_command = num_of_commands(minishell);
	if (i != num_of_command - 1)
	{
		if (pipe(curr_pipe) == -1)
			exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		child(curr_pipe, i, num_of_command);
		exec_cmd(command, minishell);
	}
	else
	{
		child_pids[i] = pid;
		parent(curr_pipe, i);
	}
}


void pipex(t_shell *minishell)
{
	int		i;
	int		fd;
	int		pid;
	pid_t	*child_pids;
	t_token	*curr;

	i = 0;
	child_pids = (pid_t *)malloc(sizeof(pid_t) * num_of_commands(minishell));
	if (child_pids == NULL)
		exit(EXIT_FAILURE);
	curr = minishell->cmd_list;
	while (curr != NULL)
	{
		printf("token currently processing: %s\n", curr->token);
		/***
		if (curr->type == T_LEFT_SHIFT)
		{
			fd = here_doc(minishell, curr->token);
			if (fd == -1)
				exit(EXIT_FAILURE);
			close(fd);
			curr = curr->next;
		} **/
		if (curr->next != NULL && !ft_strncmp(curr->token, "cat", 3) == 0)
		{
			(void)printf("skipped cat\n");
		}
		if (curr->type == T_LESSER_THAN || curr->type == T_LEFT_SHIFT)
		{
			fd = redirect_input(minishell, curr);
			pid = fork();
			printf("pid: %d\n", pid);
			if (!pid)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
				exec_cmd(curr->prev->token, minishell);
			}
			else
			{
				printf("df pid: %d\n", pid);
				close(fd);
				waitpid(pid, NULL, 0);
			}
			curr = curr->next;
		}
		else if (curr->type == T_GREATER_THAN || curr->type == T_RIGHT_SHIFT)
			redirect_output(curr);
		else if (curr->type == T_IDENTIFIER)
		{
			do_pipe(i++, child_pids, curr->token, minishell);
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
	exit(EXIT_SUCCESS);
}
