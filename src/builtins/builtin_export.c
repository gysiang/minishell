/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:05:01 by axlee             #+#    #+#             */
/*   Updated: 2024/06/19 15:07:09 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_export(t_shell *minishell)
{
	t_token	*tokens;
	t_token	*current;
	int		result;

	if (!minishell || !minishell->cmd_list)
	{
		printf("No command list provided.\n");
		return (0);
	}
	tokens = minishell->cmd_list;
	current = tokens->next;
	if (!current)
	{
		print_vars(minishell);
		return (0);
	}
	result = 0;
	while (current)
	{
		result = save_var(minishell, current->token);
		if (result != 0)
			return (result);
		current = current->next;
	}
	return (result);
}
