/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:03:37 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/08 18:16:31 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/***
static void	signal_free(t_shell *minishell)
{
	if (minishell)
		free_and_exit(minishell, 130);
}
**/

static void	signal_exit(int signal_number)
{
	(void)signal_number;
	exit(0);
}

// Need to reduce the length of this line
static void	error_eof(char *end_of_file)
{
	ft_putstr_fd("minishell: warning: here_document delimited by", 2);
	ft_putstr_fd("end-of-file (wanted ", 2);
	ft_putstr_fd(end_of_file, 2);
	ft_putendl_fd(")", 2);
}

static char *join_and_free(char *s1, const char *s2)
{
	char *joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

static char *expand_env_variable(char *str, t_shell *minishell)
{
	char *start;
	char *end;
	char *var_name;
	char *env_value;
	char *result;
	size_t len;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while ((start = ft_strchr(str, '$')))
	{
		len = start - str;
		result = join_and_free(result, ft_substr(str, 0, len));
		end = start + 1;
		while (ft_isalnum(*end) || *end == '_')
			end++;
		var_name = ft_substr(start, 1, end - start - 1);
		env_value = get_env_value(minishell, var_name);
		free(var_name);
		if (!env_value)
			env_value = ft_strdup("");
		result = join_and_free(result, env_value);
		free(env_value);
		str = end;
	}
	result = join_and_free(result, ft_strdup(str));
	return (result);
}

static void	here_doc_read(t_shell *minishell, int *pipe_fds, char *delimiter)
{
	char	*str;
	size_t	delimiter_len;
	char *expanded_str;
	(void)	minishell;

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
		if (ft_strchr(str, '$'))
		{
			expanded_str = expand_env_variable(str, minishell);
			if (expanded_str)
			{
				write(pipe_fds[1], expanded_str, ft_strlen(expanded_str));
				free(expanded_str);
			}
		}
		else
			write(pipe_fds[1], str, ft_strlen(str));
		write(pipe_fds[1], "\n", 1);
	}
	free(str);
	close(pipe_fds[1]);
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
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, WUNTRACED);
		if (WEXITSTATUS(status) == SIGINT)
		{
			close(pipe_des[0]);
			close(pipe_des[1]);
			return (-1);
		}
	}
	close(pipe_des[1]);
	minishell->input_fd = pipe_des[0];
	return (0);
}
