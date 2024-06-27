/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:03:37 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/27 14:17:15 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_if_needed(char *str, t_shell *minishell)
{
	char	*expanded_str;

	if (ft_strchr(str, '$'))
	{
		expanded_str = expand_env_variable(str, minishell);
		if (expanded_str)
			return (expanded_str);
	}
	return (ft_strdup(str));
}

static void	write_to_pipe(int fd, const char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

static void	here_doc_read(t_shell *minishell, int *pipe_fds,
		char *delimiter, int i)
{
	char	*str;
	char	*expanded_str;

	signal(SIGINT, signal_exit);
	while (1)
	{
		if (!read_input(&str, delimiter, i, minishell))
			break ;
		if (is_delimiter(str, delimiter))
			break ;
		expanded_str = expand_if_needed(str, minishell);
		if (expanded_str)
		{
			write_to_pipe(pipe_fds[1], expanded_str);
			free(expanded_str);
		}
	}
	free(str);
	close(pipe_fds[1]);
	close(pipe_fds[0]);
}

int	execute_parent(int pid, int *pipe_des)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, WUNTRACED);
	if (WEXITSTATUS(status) == SIGINT)
	{
		close(pipe_des[0]);
		close(pipe_des[1]);
		return (-1);
	}
	close(pipe_des[1]);
	return (pipe_des[0]);
}

int	here_doc(t_shell *minishell, char *delimiter, int i)
{
	int	pipe_des[2];
	int	pid;
	int	input_fd;

	if (pipe(pipe_des) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		here_doc_read(minishell, pipe_des, delimiter, i);
		free_shell(minishell);
		exit(0);
	}
	else
	{
		input_fd = execute_parent(pid, pipe_des);
		if (input_fd == -1)
			return (-1);
		minishell->input_fd = input_fd;
	}
	return (0);
}
