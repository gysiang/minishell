/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:03:37 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/30 16:54:56 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_free(t_shell *minishell)
{
	if (minishell)
		free_and_exit(minishell, 130);
}

static void	signal_exit(int signal_number)
{
	(void)signal_number;
	printf("\n");
	signal_free(NULL);
}

// Need to reduce the length of this line
static void	error_eof(char *end_of_file)
{
	ft_putstr_fd("minishell: warning: here_document delimited by end-of-file (wanted ", 2);
	ft_putstr_fd(end_of_file, 2);
	ft_putendl_fd(")", 2);
}

static void	here_doc_read(t_shell *minishell, int *pipe_fds, char *delimiter)
{
	char	*str;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	signal(SIGINT, signal_exit);
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			printf("End of file reached\n");
			error_eof(delimiter);
			break ;
		}
		if (!ft_strncmp(str, delimiter, delimiter_len + 1))
			break ;
		write(pipe_fds[1], str, ft_strlen(str));
		write(pipe_fds[1], "\n", 1);
	}
	free(str);
	close(pipe_fds[1]);
	free_and_exit(minishell, 0);
}

int	here_doc(t_shell *minishell, char *delimiter)
{
	int	pipe_des[2];
	int	status;
	int	pid;

	printf("entered into heredoc\n");
	if (pipe(pipe_des) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		here_doc_read(minishell, pipe_des, delimiter);
		exit(0);
	}
	waitpid(pid, &status, WUNTRACED);
	if (WEXITSTATUS(status) == 130)
	{
		close(pipe_des[0]);
		close(pipe_des[1]);
		return (-1);
	}
	close(pipe_des[1]);
	minishell->input_fd = pipe_des[0];
	return (0);
}
