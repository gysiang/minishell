/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:26:05 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/25 20:15:22 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection_type(t_token *curr)
{
	if (!curr)
		return (0);
	if (curr->type == T_LEFT_SHIFT || curr->type == T_LESSER_THAN
		|| curr->type == T_GREATER_THAN || curr->type == T_RIGHT_SHIFT)
		return (1);
	return (0);
}

int	check_for_redirections(t_shell *minishell)
{
	t_token	*curr;
	int		i;

	i = 0;
	curr = minishell->cmd_list;
	while (curr)
	{
		if (check_redirection_type(curr))
			return (i);
		curr = curr->next;
		i++;
	}
	return (0);
}

int	num_of_args(t_token *curr)
{
	int		i;

	i = -1;
	while (curr)
	{
		if (curr->type == T_IDENTIFIER)
		{
			i++;
		}
		curr = curr->next;
	}
	return (i);
}

/** *
	while (curr != NULL && curr->next != NULL && check_redirection_type(curr))
	{
		minishell->redir_no += 1;
		handle_redirection(minishell, curr);
		if (curr->next->next != NULL)
			curr = curr->next->next;
		else
			break ;
	}
	**/

void	get_no_of_redir(t_token *curr, t_shell *minishell)
{
	while (curr != NULL && curr->next != NULL && check_redirection_type(curr))
	{
		minishell->redir_no += 1;
		if (curr->next->next != NULL)
			curr = curr->next->next;
		else
			break ;
	}
}
