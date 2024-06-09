/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:00:03 by axlee             #+#    #+#             */
/*   Updated: 2024/06/09 11:05:59 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_special_env_variable(char *result, int *i, int *j, t_shell *minishell)
{
    char *expanded;

    expanded = ft_itoa(minishell->last_return); // Convert last return value to string
    strcpy(&result[*j], expanded);
    *j += strlen(expanded);
    free(expanded);
    *i += 2; // Skip past the $?
}

static void handle_env_variable_expansion(char *str, char *result, int *i, int *j, t_shell *minishell)
{
    char *var_start;
    char *var_end;
    int var_len;
    char *var_name;
    char *expanded;

    if (str[*i + 1] == '?')
        handle_special_env_variable(result, i, j, minishell);
    else
    {
        var_start = &str[*i + 1];
        var_end = var_start;
        while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
            var_end++;
        var_len = var_end - var_start;
        var_name = strndup(var_start, var_len);
        expanded = get_env_value(minishell, var_name);
        free(var_name);
        if (expanded)
        {
            strcpy(&result[*j], expanded);
            *j += strlen(expanded);
        }
        *i += var_len + 1;
    }
}

static void initialize_parse_variables(t_token *token, char **str, int *len, char **result, int *i, int *j)
{
    *str = token->token;
    *len = ft_strlen(*str);
    *result = malloc(*len + 1); // Allocate enough space for the result
    *i = 0;
    *j = 0;
}

static void process_character(char *str, char *result, int *i, int *j, t_shell *minishell)
{
    if (str[*i] == '\"') // Skip double quotes
        (*i)++;
    else if (str[*i] == '$')
    {
        // Handle environment variable expansion
        if (str[*i + 1] == '\0' || (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_' && str[*i + 1] != '?'))
        {
            result[(*j)++] = '$'; // Treat as a literal $
            (*i)++;
        }
        else
            handle_env_variable_expansion(str, result, i, j, minishell);
    }
    else
    {
        result[(*j)++] = str[*i];
        (*i)++;
    }
}

void parse_double_quotes(t_token *token, t_shell *minishell)
{
    char *str;
    int len;
    char *result;
    int i;
    int j;

    initialize_parse_variables(token, &str, &len, &result, &i, &j);
    if (!result)
        return;
    while (i < len)
        process_character(str, result, &i, &j, minishell);
    result[j] = '\0'; // Null-terminate the result
    free(token->token);
    token->token = result;
    token->is_single_quoted = 0; // Set the flag to indicate double quotes were processed
}
