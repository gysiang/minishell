
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

static int	assign_last(t_token *c)
{
	if (c->next != NULL)
		return (0);
	else
		return (1);
}
/***
static void print_fd_contents(int fd) {
    char buffer[1024];  // Buffer to hold the read data
    ssize_t bytes_read; // Number of bytes read by read()

    // Read from the file descriptor until there's no more data
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        // Print the data read from the file descriptor
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    // Check for read errors
    if (bytes_read == -1) {
        perror("read");
    }
}
**/

void	execute_command(int i, t_token *curr, t_shell *minishell, int last_command)
{
	int	pipe_fd[2];
	int pid;
	int num_of_command;
	int status;

	//printf("executing %s\n", curr->token);
	num_of_command = num_of_commands(minishell);
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
			if (curr->next && curr->next->type == T_LEFT_SHIFT)
			{
				if (here_doc(minishell, curr->next->next->token) != -1)
				{
					dup2(minishell->heredoc_fd, STDIN_FILENO);
					close(minishell->heredoc_fd);
				}
			}
			if (curr->next && (curr->next->type == T_LESSER_THAN || curr->next->type == T_LEFT_SHIFT))
			{
				if (redirect_input(minishell,curr->next->next->token) != -1)
				{
					dup2(minishell->heredoc_fd, STDIN_FILENO);
					close(minishell->heredoc_fd);
				}
			}
			else
			{
				dup2(pipe_fd[0], STDIN_FILENO);
				close(pipe_fd[1]);
			}
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



void pipex(t_shell *minishell)
{
	int		i;
	//int		fd;
	int		is_last_command;
	//pid_t	*child_pids;
	t_token	*curr;

	i = 0;
	is_last_command = 0;
	curr = minishell->cmd_list;
	while (curr != NULL)
	{
		//printf("curr token processing %s\n", curr->token);
		if (curr->type == T_LEFT_SHIFT)
		{
			curr = curr->next;
		}
		else if (curr->type == T_LESSER_THAN)
		{
			//int p_fd = redirect_input(minishell, curr);

			/***
			int pid = fork();
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
			**/
			curr = curr->next;
		}
		/***
		else if (curr->type == T_GREATER_THAN || curr->type == T_RIGHT_SHIFT)
			redirect_output(curr);
		**/
		else if (curr->type == T_IDENTIFIER)
		{
			is_last_command = assign_last(curr);
			if (curr->next && curr->next->type == T_LESSER_THAN)
			{
				is_last_command = 1;
			}
			if (curr->next && curr->next->type == T_LEFT_SHIFT)
			{
				//here_doc(minishell, curr->next->next->token);
				//printf("printing from heredoc_fd:\n");
				//print_fd_contents(minishell->heredoc_fd);
				//dup2(minishell->heredoc_fd, STDIN_FILENO);
				//close(minishell->heredoc_fd);
				is_last_command = 1;
			}
			execute_command(i++, curr, minishell, is_last_command);
		}
		curr = curr->next;
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
