/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:35:24 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 12:49:45 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_pointers(t_token *tokens)
{
	t_token	*prev_token;
	t_token	*curr_token;

	prev_token = NULL;
	curr_token = tokens;
	while (curr_token != NULL)
	{
		curr_token->prev = prev_token;
		if (prev_token != NULL)
			prev_token->next = curr_token;
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
	if (prev_token != NULL)
		prev_token->next = NULL;
}

void	parse_token(t_token *token, t_shell *minishell)
{
	char	*str;
	int		len;

	str = token->token;
	len = ft_strlen(str);
	if (len > 1)
	{
		if (str[0] == '\'' && str[len - 1] == '\'')
			parse_single_quotes(token);
		else if (str[0] == '\"' && str[len - 1] == '\"')
			parse_double_quotes(token, minishell);
		else
			remove_embedded_quotes(token);
	}
	str = token->token;
	len = ft_strlen(str);
	if (strchr(token->token, '$') && !token->is_single_quoted)
		parse_value(token, minishell);
}

t_token	*token_parser(t_token *token_lst, t_shell *minishell)
{
	t_token	*curr;

	curr = token_lst;
	while (curr != NULL)
	{
		parse_token(curr, minishell);
		curr = curr->next;
	}
	set_token_pointers(token_lst);
	join_identifier_tokens(token_lst);
	return (token_lst);
}

