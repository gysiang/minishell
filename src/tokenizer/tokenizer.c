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
        char *text = ft_strndup(start, *line - start);
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
    char quote_type;
    char *start;
    int length;
    char *quoted_content;
    char *literal_quote;

    quote_type = **line;
    start = *line; // Include the opening quote
    (*line)++; // Move past the opening quote
    while (**line && **line != quote_type) // Find the closing quote
        (*line)++;
    if (**line == quote_type)
    {
        (*line)++; // Move past the closing quote
        length = *line - start;
        quoted_content = (char *)malloc(length + 1);
        if (quoted_content)
        {
            strncpy(quoted_content, start, length);
            quoted_content[length] = '\0';
            token_add_back(token_lst, quoted_content, T_IDENTIFIER);
            free(quoted_content);
        }
    }
    else
    {
        // If no closing quote is found, treat the opening quote as a literal character
        literal_quote = (char *)malloc(2);
        if (literal_quote) {
            literal_quote[0] = quote_type;
            literal_quote[1] = '\0';
            token_add_back(token_lst, literal_quote, T_IDENTIFIER);
            free(literal_quote);
        }
    }
}


t_token *token_processor(char *line, t_shell *minishell)
{
    t_token *token_lst;
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