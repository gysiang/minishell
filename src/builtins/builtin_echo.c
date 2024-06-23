/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/06/24 02:47:07 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	print_input_fd(t_shell *minishell)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	printf("\n");
	bytes_read = read(minishell->input_fd, buffer, sizeof(buffer) - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
		bytes_read = read(minishell->input_fd, buffer, sizeof(buffer) - 1);
	}
}*/
static void	handle_identifier_token(t_token *current, int *first, int fd)
{
	if (ft_strcmp(current->token, "") != 0)
	{
		if (!(*first))
			write(fd, " ", 1);
		write(fd, current->token, ft_strlen(current->token));
		*first = 0;
	}
}

static int	handle_redirection_echo(t_token **current, t_shell *minishell)
{
	int	fd;

	if ((*current)->next != NULL && (*current)->next->type == T_FILE)
	{
		fd = open((*current)->next->token, O_RDONLY);
		if (fd == -1)
		{
			perror("minishell");
			minishell->last_return = 1;
			return (0);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		*current = (*current)->next->next;
		return (1);
	}
	return (0);
}

static void	print_tokens(t_token *current, t_shell *minishell, int newline,
		int fd)
{
	int		first;
	char	buffer[1024];
	ssize_t	bytes_read;

	first = 1;
	while (current != NULL)
	{
		if (current->type == T_IDENTIFIER)
			handle_identifier_token(current, &first, fd);
		else if (check_redirection_type(current))
		{
			if (handle_redirection_echo(&current, minishell))
				continue ;
		}
		else
			break ;
		current = current->next;
	}
	if (minishell->flag)
	{
		while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[bytes_read] = '\0';
			write(STDOUT_FILENO, buffer, bytes_read);
		}
		close(fd);
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}

void	minishell_echo(t_shell *minishell)
{
	t_token	*current;
	int		newline;
	int		fd;

	newline = 1;
	if (minishell->cmd_list == NULL)
		return ;
	current = minishell->cmd_list;
	while (current && (current->type != T_IDENTIFIER
			|| ft_strcmp(current->token, "") == 0))
		current = current->next;
	if (current && ft_strcmp(current->token, "echo") == 0)
		current = current->next;
	if (current && ft_strcmp(current->token, "-n") == 0)
	{
		newline = 0;
		current = current->next;
	}
	fd = STDOUT_FILENO;
	if (minishell->input_fd != -1)
	{
		fd = minishell->input_fd;
	}
	print_tokens(current, minishell, newline, fd);
}
