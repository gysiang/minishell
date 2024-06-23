/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:05:01 by axlee             #+#    #+#             */
/*   Updated: 2024/06/23 19:40:20 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_export_tokens(t_token *current, t_shell *minishell)
{
	int	result;

	result = 0;
	while (current)
	{
		if (current->type != T_IDENTIFIER)
			break ;
		result = save_var(minishell, current->token);
		if (result != 0)
			return (result);
		current = current->next;
	}
	return (result);
}

int	minishell_export(t_shell *minishell)
{
	t_token	*current;

	if (!minishell || !minishell->cmd_list)
	{
		printf("No command list provided.\n");
		return (0);
	}
	current = minishell->cmd_list->next;
	if (!current)
	{
		print_vars(minishell);
		return (0);
	}
	return (process_export_tokens(current, minishell));
}
