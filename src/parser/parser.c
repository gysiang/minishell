/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:35:24 by axlee             #+#    #+#             */
/*   Updated: 2024/06/06 19:16:05 by axlee            ###   ########.fr       */
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

void remove_embedded_quotes(t_token *token)
{
   char *str;
    char *new_str;
   int len;
   int first_quote_index;
   int last_quote_index;
   char quote_char;
   int i;
   int found_in_between;


   str = token->token;
   len = strlen(str);
   first_quote_index = -1;
   last_quote_index = -1;
   quote_char = '\0';
   // Find the first quote
   i = 0;
   while (i < len)
   {
       if (str[i] == '\'' || str[i] == '\"') {
           first_quote_index = i;
           quote_char = str[i];
           break;
       }
       i++;
   }
   // Find the last quote
   i = len - 1;
   while (i > first_quote_index)
   {
       if (str[i] == quote_char)
	   {
           last_quote_index = i;
           break;
       }
       i--;
   }
   // Check if there are no similar quotes in between
   found_in_between = 0;
   i = first_quote_index + 1;
   while (i < last_quote_index)
   {
       if (str[i] == quote_char)
	   {
           found_in_between = 1;
           break;
       }
       i++;
   }
   // Check if the quotes are adjacent (no characters in between)
   if (last_quote_index == first_quote_index + 1) 
       found_in_between = 1; // Treat adjacent quotes as a special case of in-between quotes
   if (!found_in_between && first_quote_index != -1 && last_quote_index != -1)
   {
       // Remove the quotes
       new_str = malloc(len - 1); // Allocate space for new string without the two quotes
       if (!new_str) return;
       memcpy(new_str, str, first_quote_index); // Copy part before the first quote
       memcpy(new_str + first_quote_index, str + first_quote_index + 1, last_quote_index - first_quote_index - 1); // Copy part between the quotes
       memcpy(new_str + last_quote_index - 1, str + last_quote_index + 1, len - last_quote_index - 1); // Copy part after the last quote
       new_str[len - 2] = '\0'; // Null-terminate the new string
       free(token->token);
       token->token = new_str;
   }
}


void parse_token(t_token *token, t_shell *minishell)
{
   char *str;
   int len;


   str = token->token;
   len = ft_strlen(str);
   // Handle quotes at the boundaries
   if (len > 1 && ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len - 1] == '\"')))
   {
       if (str[0] == '\'')
           parse_single_quotes(token);
       else
           parse_double_quotes(token, minishell);
   }
   else // Remove embedded quotes for cases like hello'world'
       remove_embedded_quotes(token);
   // Handle variable expansion
   if (strchr(token->token, '$') && !token->is_single_quoted)
       parse_value(token, minishell);
}

/*void parse_token(t_token *token, t_shell *minishell)
{
    char *str;
    int len;

    str = token->token;
    len = ft_strlen(str);
    if ((len > 1 && str[0] == '\'' && str[len - 1] == '\'') || (len > 1 && str[0] == '\"' && str[len - 1] == '\"'))
    {
		if (str[0] == '\'')
        	parse_single_quotes(token);
		else
			parse_double_quotes(token, minishell);
	}
    else if (strchr(token->token, '$'))
	{
		if(!token->is_single_quoted)
			parse_value(token, minishell);
	}
    else if (strchr(token->token, '$'))
        parse_value(token, minishell);
}*/

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
