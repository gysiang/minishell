/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/07/06 22:52:38 by gyong-si         ###   ########.fr       */
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

static void	handle_identifier_token(t_token *current)
{
	if (ft_strcmp(current->token, "") != 0)
	{
		printf("%s", current->token);
		if (current->space == 1)
			printf(" ");
	}
}

static void	print_tokens(t_token *current, t_shell *minishell, int newline)
{
	while (current != NULL)
	{
		if (current->type == T_IDENTIFIER)
			handle_identifier_token(current);
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
		safe_close(&minishell->input_fd);
	}
	if (newline)
		printf("\n");
}

void	minishell_echo(t_token *curr, t_shell *minishell)
{
	t_token	*current;
	int		newline;

	newline = 1;
	current = curr;
	if (current && ft_strcmp(current->token, "echo") == 0)
		current = current->next;
	while (current && ft_strcmp(current->token, "-n") == 0)
	{
		newline = 0;
		current = current->next;
	}
	print_tokens(current, minishell, newline);
}
