/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:54:35 by axlee             #+#    #+#             */
/*   Updated: 2024/07/06 23:00:01 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_unclosed_quotes(const char *str)
{
	int		in_single_quote;
	int		in_double_quote;
	size_t	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (in_single_quote || in_double_quote);
}

void	set_spaces(t_token *token_lst)
{
	t_token	*curr;

	curr = token_lst;
	while (curr != NULL)
	{
		if (curr && curr->type == T_IDENTIFIER
			&& curr->next != NULL && curr->next->type != T_IDENTIFIER)
		{
			curr->space = 0;
		}
		curr = curr->next;
	}
}
