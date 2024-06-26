/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:32:12 by axlee             #+#    #+#             */
/*   Updated: 2024/06/26 17:34:39 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_command(char *token)
{
	int					i;
	static const char	*commands[] = {"cd", "echo", "exit", "unset", "pwd",
		"env", "export", NULL};

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(token, commands[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	is_part_of_command_arguments(t_token *token)
{
	t_token	*prev;

	prev = token;
	while (prev != NULL && prev->type == T_IDENTIFIER)
	{
		if (is_command(prev->token))
			return (true);
		prev = prev->prev;
	}
	return (false);
}
