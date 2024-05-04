/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:31:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/04 22:30:27 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char 	*concat_token(const char *token1, const char *token2)
{
	size_t	len1;
	size_t	len2;
	size_t	total_len;
	char	*joined_str;

	len1 = ft_strlen(token1);
	len2 = ft_strlen(token2);
	total_len = len1 + len2 + 2;
	joined_str = (char *)malloc(total_len);
	if (!joined_str)
		return (NULL);
	ft_copy(joined_str, token1, len1);
	ft_strcat(joined_str, " ");
	ft_strcat(joined_str, token2);
	return (joined_str);
}

void	join_identifier_tokens(t_token *lst)
{
	char *joined;
	t_token *curr;
	t_token *next;
	int	merged;

	merged = 1;
	while (merged)
	{
		merged = 0;
		curr = lst;
		while (curr != NULL && curr->next != NULL)
		{
			if (curr->type == T_IDENTIFIER && curr->next->type == T_IDENTIFIER)
			{
				joined = concat_token(curr->token, curr->next->token);
				if (joined != NULL)
				{
					free(curr->token);
					curr->token = joined;
					next = curr->next;
					curr->next = next->next;
					free(next);
					merged = 1;
				}
				merged = 1;
				break ;
			}
			curr = curr->next;
		}
	}
}