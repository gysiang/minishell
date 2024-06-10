/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:13:57 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 13:01:45 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print the linked list that holds the tokens;
void	print_tokenlst(t_token *token_lst)
{
	t_token	*curr;

	curr = token_lst;
	while (curr != NULL)
	{
		printf("token: %s\n", curr->token);
		printf("token type: %d\n", curr->type);
		curr = curr->next;
	}
}

void	handle_environment_variable(char **line, t_token **token_lst,
		t_shell *minishell)
{
	char	*start;
	char	*var_name;
	char	*expanded;
	char	*result;
	int		var_len;

	start = *line;
	// Move past the dollar sign
	(*line)++;
	start = *line;
	// Special case for $?
	if (**line == '?')
	{
		(*line)++;
		expanded = ft_itoa(minishell->last_return);
		// Convert last return value to string
		var_len = strlen(expanded);
		result = malloc(var_len + 1);
		if (result)
		{
			strcpy(result, expanded);
			free(expanded);
			// Handle the rest of the line as part of the same token
			while (**line && !ft_iswhitespace(*line) && **line != '$'
				&& **line != '\'' && **line != '\"')
			{
				result = ft_realloc(result, strlen(result) + 2);
				strncat(result, *line, 1);
				(*line)++;
			}
			token_add_back(token_lst, result, T_IDENTIFIER);
			free(result);
		}
		return ;
	}
	// Find the end of the variable name
	while (**line && (ft_isalnum(**line) || **line == '_'))
		(*line)++;
	var_len = *line - start;
	var_name = ft_strndup(start, var_len);
	expanded = get_env_value(minishell, var_name);
	free(var_name);
	if (expanded)
	{
		// Allocate space for the result
		result = malloc(strlen(expanded) + 1);
		if (result)
		{
			strcpy(result, expanded);
			free(expanded);
			// Handle the rest of the line as part of the same token
			while (**line && !ft_iswhitespace(*line) && **line != '$'
				&& **line != '\'' && **line != '\"')
			{
				result = ft_realloc(result, strlen(result) + 2);
				strncat(result, *line, 1);
				(*line)++;
			}
			token_add_back(token_lst, result, T_IDENTIFIER);
			free(result);
		}
	}
	else
	{
		// If the variable is not found, add the original text
		result = ft_strndup(start - 1, var_len + 1);
		token_add_back(token_lst, result, T_IDENTIFIER);
		free(result);
	}
}
