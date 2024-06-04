/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:35:24 by axlee             #+#    #+#             */
/*   Updated: 2024/06/04 14:49:43 by axlee            ###   ########.fr       */
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

/*void	handle_cd_command(t_token **curr, t_shell *minishell)
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
}*/

void parse_token(t_token *token, t_shell *minishell)
{
    char *str;
    int len;

    str = token->token;
    len = ft_strlen(str);
    if (len > 1 && str[0] == '\'' && str[len - 1] == '\'')
    {
        token->is_single_quoted = 1;
        parse_single_quotes(token);
    }
    else if (len > 1 && str[0] == '\"' && str[len - 1] == '\"')
        parse_double_quotes(token);
    /*else if (ft_strncmp(str, "$?", 2) == 0)
        handle_exit_status_with_suffix(token, minishell, str + 2);*/
    else if (!token->is_single_quoted && strchr(token->token, '$'))
        parse_value(token, minishell);
    else if (strchr(token->token, '$')) // Handle unquoted tokens
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
