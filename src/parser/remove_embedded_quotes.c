/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_embedded_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:26:28 by axlee             #+#    #+#             */
/*   Updated: 2024/06/09 19:44:01 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_token_if_needed(t_token *token, char *new_str)
{
	if (new_str != NULL)
	{
		free(token->token);
		token->token = NULL;
		token->token = new_str;
	}
}

void	process_quote_removal(char *str, int len, t_token *token)
{
	int		first_quote_index;
	int		last_quote_index;
	char	quote_char;
	int		found_in_between;
	char	*new_str;

	first_quote_index = find_first_quote(str, len);
	if (first_quote_index != -1)
	{
		quote_char = str[first_quote_index];
		last_quote_index = find_last_quote(str, len, first_quote_index,
				quote_char);
		found_in_between = check_quotes_in_between(str, first_quote_index,
				last_quote_index, quote_char);
		if (!found_in_between && last_quote_index != -1)
		{
			new_str = remove_quotes(str, first_quote_index, last_quote_index,
					len);
			update_token_if_needed(token, new_str);
		}
	}
}

void	remove_embedded_quotes(t_token *token)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(ft_strlen(token->token) + 1);
	if (!new_str)
		return ;
	i = 0;
	j = 0;
	while (token->token[i])
	{
		if (token->token[i] != '\'' && token->token[i] != '\"')
			new_str[j++] = token->token[i];
		i++;
	}
	new_str[j] = '\0';
	update_token_if_needed(token, new_str);
}