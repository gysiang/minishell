/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/06/24 13:46:00 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_input_fd(t_shell *minishell)
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
}

static void	handle_identifier_token(t_token *current, int *first)
{
	if (ft_strcmp(current->token, "") != 0)
	{
		if (!(*first))
			printf(" ");
		printf("%s", current->token);
		*first = 0;
	}
}
/** *
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
} **/

static void	print_tokens(t_token *current, t_shell *minishell, int newline)
{
	int		first;

	first = 1;
	while (current != NULL)
	{
		if (current->type == T_IDENTIFIER)
			handle_identifier_token(current, &first);
		else if (current->type == T_FILE || check_redirection_type(current))
		{
			current = current->next->next;
			continue ;
		}
		else
			break ;
		current = current->next;
	}
	if (minishell->flag)
	{
		print_input_fd(minishell);
		close(minishell->input_fd);
	}
	if (newline)
		printf("\n");
}

void	minishell_echo(t_token *curr, t_shell *minishell)
{
	t_token	*current;
	int		newline;
	//int		fd;

	newline = 1;
	current = curr;
	/** *
	while (current && (current->type != T_IDENTIFIER
			|| ft_strcmp(current->token, "") == 0))
		current = current->next;
	**/
	if (current && ft_strcmp(current->token, "echo") == 0)
		current = current->next;
	if (current && ft_strcmp(current->token, "-n") == 0)
	{
		newline = 0;
		current = current->next;
	}
	print_tokens(current, minishell, newline);
}
