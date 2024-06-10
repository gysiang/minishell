/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:13:57 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 12:15:37 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c && *s != '|')
	{
		i++;
		s++;
	}
	return (i);
}

int add_symbol_lst(char **line, t_token_type type, t_token **token_lst)
{
    int     word_len;
    char    *symbol;

    // Determine the length of the symbol based on its type
    if (type == T_LEFT_SHIFT || type == T_RIGHT_SHIFT)
        word_len = 2;  // "<<" or ">>"
    else
        word_len = 1;  // "|", "<", ">"
    symbol = (char *)malloc(word_len + 1);
    if (!symbol)
        return (0);
    ft_copy(symbol, *line, word_len);
    symbol[word_len] = '\0';  // Ensure null termination
    token_add_back(token_lst, symbol, type);
    free(symbol);
    // Increment the line pointer based on the length of the symbol
    (*line) += word_len;
    return (0);
}

int add_command_lst(char **line, t_token **token_lst)
{
    while (ft_iswhitespace(*line)) // Skip leading whitespace
        (*line)++;
    char *start = *line;
    while (**line && !ft_iswhitespace(*line) && **line != '|' && **line != '<' && **line != '>' && **line != '\'' && **line != '\"') // Find end of the word
        (*line)++;
    if (**line == '\"' || **line == '\'') // Handle quoted strings
    {
        char quote_type = **line;
        (*line)++; // Move past the opening quote
        while (**line && **line != quote_type) // Find the closing quote
            (*line)++;
        if (**line == quote_type)
            (*line)++; // Move past the closing quote
    }
    if (*line != start)
    {
        char *cmd = ft_strndup(start, *line - start);
        token_add_back(token_lst, cmd, T_IDENTIFIER);
        free(cmd);
    }
    return (0);
}


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

void handle_environment_variable(char **line, t_token **token_lst, t_shell *minishell)
{
    char *start = *line;
    char *var_name;
    char *expanded;
    char *result;
    int var_len;

    // Move past the dollar sign
    (*line)++;
    start = *line;

    // Special case for $?
    if (**line == '?')
    {
        (*line)++;
        expanded = ft_itoa(minishell->last_return); // Convert last return value to string
        var_len = strlen(expanded);
        result = malloc(var_len + 1);
        if (result)
        {
            strcpy(result, expanded);
            free(expanded);
            // Handle the rest of the line as part of the same token
            while (**line && !ft_iswhitespace(*line) && **line != '$' && **line != '\'' && **line != '\"')
            {
                result = ft_realloc(result, strlen(result) + 2);
                strncat(result, *line, 1);
                (*line)++;
            }
            token_add_back(token_lst, result, T_IDENTIFIER);
            free(result);
        }
        return;
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
            while (**line && !ft_iswhitespace(*line) && **line != '$' && **line != '\'' && **line != '\"')
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