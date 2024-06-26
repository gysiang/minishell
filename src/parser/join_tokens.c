/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:31:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/26 17:34:30 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_token(const char *token1, const char *token2)
{
	size_t	len1;
	size_t	len2;
	size_t	total_len;
	char	*joined_str;

	len1 = ft_strlen(token1);
	len2 = ft_strlen(token2);
	total_len = len1 + len2 + 2;
	joined_str = (char *)malloc(total_len + 1);
	if (!joined_str)
		return (NULL);
	ft_copy(joined_str, token1, len1);
	ft_strcat(joined_str, " ");
	ft_strcat(joined_str, token2);
	return (joined_str);
}

void	merge_identifier_tokens(t_token *curr)
{
	char	*joined;
	t_token	*next;

	joined = concat_token(curr->token, curr->next->token);
	if (joined)
	{
		free(curr->token);
		curr->token = joined;
		next = curr->next;
		curr->next = next->next;
		if (next->next != NULL)
			next->next->prev = curr;
		free(next->token);
		free(next);
	}
}

void	process_current_token(t_token **curr, int *merged)
{
	if (check_redirection_type(*curr))
	{
		(*curr)->next->type = T_FILE;
		*curr = (*curr)->next->next;
	}
	else if ((*curr)->type == T_IDENTIFIER
		&& (*curr)->next->type == T_IDENTIFIER && !is_command((*curr)->token)
		&& !is_command((*curr)->next->token)
		&& !is_part_of_command_arguments((*curr)->next))
	{
		merge_identifier_tokens(*curr);
		*merged = 1;
	}
	else
		*curr = (*curr)->next;
}

void	join_identifier_tokens(t_token *lst)
{
	t_token	*curr;
	int		merged;

	merged = 1;
	while (merged)
	{
		merged = 0;
		curr = lst;
		while (curr != NULL && curr->next != NULL)
		{
			process_current_token(&curr, &merged);
			if (merged)
				break ;
		}
	}
}
