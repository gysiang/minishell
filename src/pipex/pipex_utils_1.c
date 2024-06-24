/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 08:32:37 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/24 23:00:41 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_of_commands(t_shell *minishell)
{
	int		i;
	t_token	*curr_token;

	i = 0;
	curr_token = minishell->cmd_list;
	i = 0;
	while (curr_token != NULL)
	{
		if (curr_token->type == T_IDENTIFIER)
			i++;
		curr_token = curr_token->next;
	}
	return (i);
}

int	pipe_found(t_token *curr)
{
	while (curr != NULL)
	{
		if (curr->type == T_PIPE)
			return (1);
		else
			curr = curr->next;
	}
	return (0);
}

int	num_of_redirections(t_shell *minishell)
{
	int		i;
	t_token	*curr_token;

	i = 0;
	curr_token = minishell->cmd_list;
	while (curr_token != NULL)
	{
		if (check_redirection_type(curr_token))
			i++;
		curr_token = curr_token->next;
	}
	return (i);
}

int	num_of_args_or_file(t_shell *minishell)
{
	int		i;
	t_token	*curr;

	i = -1;
	curr = minishell->cmd_list;
	while (curr)
	{
		if (curr->type == T_IDENTIFIER || curr->type == T_FILE)
		{
			i++;
		}
		else
			return (i);
		curr = curr->next;
	}
	return (i);
}

t_token	*move_lst_by_index(t_token *curr, int index)
{
	while (curr != NULL && index > 0)
	{
		curr = curr->next;
		index--;
	}
	return (curr);
}
