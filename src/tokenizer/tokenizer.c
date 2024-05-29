/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:16:40 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/23 02:08:53 by axlee            ###   ########.fr       */
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
    char *end = *line;
    while (*end && !ft_iswhitespace(end)) // Find end of the word
        end++;
    if (*line != end)
    {
        char *cmd = strndup(*line, end - *line);
        token_add_back(token_lst, cmd, T_IDENTIFIER);
        free(cmd);
        *line = end; // Move line pointer past the processed token
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
    (*line)++; // Move past the dollar sign
    char *start = *line;
    while (**line && !ft_iswhitespace(*line) && **line != '/') // Find end of the variable name
        (*line)++;
    char *var_name = strndup(start, *line - start); // Extract variable name
    char *expanded = get_env_value(minishell, var_name); // Get expanded value
    free(var_name);

    if (expanded) {
        // Add the expanded variable as a token
        token_add_back(token_lst, expanded, T_IDENTIFIER);
    }

    // Check if there's more text following the variable
    if (**line != '\0') {
        // Handle the rest of the line as separate tokens
        handle_remaining_text(line, token_lst);
    }
}

void handle_remaining_text(char **line, t_token **token_lst)
{
    // Skip any whitespace immediately after the variable expansion
    while (ft_iswhitespace(*line))
        (*line)++;

    // If there's more text, treat it as a separate token
    if (**line != '\0') {
        char *start = *line;
        while (**line && !ft_iswhitespace(*line))
            (*line)++;
        char *text = strndup(start, *line - start);
        token_add_back(token_lst, text, T_IDENTIFIER);
        free(text);
    }
}

void handle_backslash(char **line, t_token **token_lst)
{
    (*line)++; // Move past the backslash
    if (**line == '\"' || **line == '\'') { // Check if it's escaping a quote
        // Start building the token from the character after the backslash
        char *start = *line; // Point to the quote
        (*line)++; // Move past the quote
        // Continue until a whitespace or a special shell character is found
        while (**line && !ft_iswhitespace(*line) && **line != '|' && **line != '<' && **line != '>')
            (*line)++;
        // Allocate and copy the token starting from the quote
        int length = *line - start;
        char *escaped_token = (char *)malloc(length + 1);
        if (escaped_token) {
            strncpy(escaped_token, start, length); // Copy starting from the quote
            escaped_token[length] = '\0';
            token_add_back(token_lst, escaped_token, T_IDENTIFIER);
            free(escaped_token);
        }
    } else {
        // Handle other characters escaped by backslash
        char escaped[2] = {**line, '\0'};
        token_add_back(token_lst, escaped, T_IDENTIFIER);
        (*line)++;
    }
}

void handle_quotes(char **line, t_token **token_lst)
{
    char quote_type = **line;
    (*line)++; // Move past the opening quote
    char *start = *line;
    while (**line && **line != quote_type) // Find the closing quote
        (*line)++;
    if (**line == quote_type) {
        int length = *line - start;
        char *quoted_content = (char *)malloc(length + 1);
        if (quoted_content) {
            strncpy(quoted_content, start, length);
            quoted_content[length] = '\0';
            token_add_back(token_lst, quoted_content, T_IDENTIFIER);
            free(quoted_content);
        }
        (*line)++; // Move past the closing quote
    } else {
        // If no closing quote is found, treat the opening quote as a literal character
        char literal_quote[2] = {quote_type, '\0'};
        token_add_back(token_lst, literal_quote, T_IDENTIFIER);
    }
}

t_token	*token_processor(char *line, t_shell *minishell)
{
	t_token	*token_lst;
	(void)minishell;
	token_lst = NULL;
	while (*line != '\0')
	{
		if (ft_iswhitespace(line))
			line++;
		else if (*line == '\\')
			handle_backslash(&line, &token_lst);
		else if (*line == '$')
			handle_environment_variable(&line, &token_lst, minishell);
		else if (*line == '\"' || *line == '\'')
			handle_quotes(&line, &token_lst);
		else if (ft_strncmp(line, "|", 1) == 0)
			add_symbol_lst(&line, T_PIPE, &token_lst);
        else if (ft_strncmp(line, "<<", 2) == 0)
			add_symbol_lst(&line, T_LEFT_SHIFT, &token_lst);
		else if (ft_strncmp(line, ">>", 2) == 0)
			add_symbol_lst(&line, T_RIGHT_SHIFT, &token_lst);
		else if (ft_strncmp(line, "<", 1) == 0)
			add_symbol_lst(&line, T_LESSER_THAN, &token_lst);
		else if (ft_strncmp(line, ">", 1) == 0)
			add_symbol_lst(&line, T_GREATER_THAN, &token_lst);
		else
		{
			add_command_lst(&line, &token_lst);
			while (ft_iswhitespace(line))
				line++;
		}
	}
	token_lst = token_parser(token_lst, minishell);
	return (token_lst);
}
