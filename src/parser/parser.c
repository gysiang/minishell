/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:35:24 by axlee             #+#    #+#             */
/*   Updated: 2024/05/17 13:50:54 by axlee            ###   ########.fr       */
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

void	handle_cd_command(t_token **curr, t_shell *minishell)
{
	t_token	*next_token;
	char	*dir;

	next_token = (*curr)->next;
	if (next_token != NULL && next_token->type == T_IDENTIFIER)
	{
		dir = next_token->token;
		if (chdir(dir) != 0)
		{
			ft_putstr_fd("minishell: cd", 2);
			minishell->last_return = 1;
		}
		else
			minishell->last_return = 0;
		*curr = next_token->next;
	}
	else
	{
		ft_putstr_fd("minishell:cd :too few arguments\n", 2);
		minishell->last_return = 1;
		*curr = (*curr)->next;
	}
}

void	parse_token(t_token *token, t_shell *minishell)
{
	if (ft_strchr(token->token, '\''))
		parse_singlequote(token);
	else if (ft_strchr(token->token, ';'))
		parse_semicolon(token);
	else if (ft_strchr(token->token, '$'))
	{
		parse_doublequote(token);
		parse_value(token, minishell);
	}
	else if (ft_strchr(token->token, '\"'))
		parse_doublequote(token);
	else if (strcmp(token->token, "cd") == 0)
		handle_cd_command(&token, minishell);
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
	join_identifier_tokens(token_lst);
	set_token_pointers(token_lst);
	return (token_lst);
}
