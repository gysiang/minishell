/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/06/16 20:32:05 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_input_fd(t_shell *minishell)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	printf("\n");
	while ((bytes_read = read(minishell->input_fd, buffer, sizeof(buffer)
				- 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
	}
}

static void	handle_token_print(t_token *current, int *first)
{
	if (current->prev && current->prev->type == T_IDENTIFIER
		&& ft_strcmp(current->prev->token, "") == 0)
		*first = 1;
	if (!(*first))
		printf(" ");
	if (ft_strcmp(current->token, "") != 0)
		printf("%s", current->token);
	else
		printf(" ");
	*first = 0;
}

static void	print_tokens(t_token *current, t_shell *minishell, int newline)
{
	int	first;

	first = 1;
	while (current != NULL)
	{
		if (current->type == T_IDENTIFIER)
			handle_token_print(current, &first);
		else if (current->type == T_IDENTIFIER && ft_strcmp(current->token,
				"") == 0)
		{
			current = current->next;
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


void	minishell_echo(t_shell *minishell)
{
	int		newline;
	t_token	*current;

	newline = 1;
	if (minishell->cmd_list == NULL)
		return ;
	if (minishell->signal_received)
		exit(1);
	current = minishell->cmd_list->next;
	if (current != NULL && ft_strcmp(current->token, "-n") == 0)
	{
		newline = 0;
		current = current->next;
	}
	print_tokens(current, minishell, newline);
}
