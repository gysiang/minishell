/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:54:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/06 19:56:10 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_single_quotes(t_token *token)
{
    char *str;
    int len;
    char *result;
    int i, j;

    str = token->token;
    len = ft_strlen(str);
    result = malloc(len + 1); // Allocate enough space for the result
    if (!result)
        return;

    i = 0;
    j = 0;
    while (i < len)
    {
        if (str[i] != '\'') // Skip single quotes
        {
            result[j] = str[i];
            j++;
        }
        i++;
    }
    result[j] = '\0'; // Null-terminate the result

    free(token->token);
    token->token = result;
    token->is_single_quoted = 1; // Set the flag to indicate single quotes were processed
}

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
    {
        handle_special_env_variable(result, i, j, minishell);
    }
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

void parse_double_quotes(t_token *token, t_shell *minishell)
{
    char *str;
    int len;
    char *result;
    int i, j;

    str = token->token;
    len = ft_strlen(str);
    result = malloc(len + 1); // Allocate enough space for the result
    if (!result)
        return;

    i = 0;
    j = 0;
    while (i < len)
    {
        if (str[i] == '\"') // Skip double quotes
        {
            i++;
            continue;
        }
        if (str[i] == '$')
        {
            // Handle environment variable expansion
            if (str[i + 1] == '\0' || (!ft_isalnum(str[i + 1]) && str[i + 1] != '_' && str[i + 1] != '?'))
            {
                result[j++] = '$'; // Treat as a literal $
                i++;
            }
            else
            {
                handle_env_variable_expansion(str, result, &i, &j, minishell);
            }
        }
        else
        {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0'; // Null-terminate the result

    free(token->token);
    token->token = result;
    token->is_single_quoted = 0; // Set the flag to indicate double quotes were processed
}

void	parse_semicolon(t_token *token)
{
	t_token	*curr;
	char	*result;
	size_t	len;

	curr = token;
	len = ft_wordlen(curr->token, ';');
	result = (char *)malloc(len + 1);
	if (!result)
		return ;
	ft_copy(result, curr->token, len);
	free(curr->token);
	curr->token = result;
}

void	handle_env_variable(t_token *curr, t_shell *minishell)
{
	char	*result;
	char	*env_value;

	result = ft_substr(curr->token, 1, ft_strlen(curr->token) - 1);
	if (!result)
		return ;
	env_value = get_env_value(minishell, result);
	free(result);
	if (!env_value)
		env_value = ft_strdup(" ");
	free(curr->token);
	curr->token = env_value;
}

void handle_exit_status(t_token *curr, t_shell *minishell)
{
    char *exit_status_str;
    int exit_status;

    exit_status = minishell->last_return;
    exit_status_str = ft_itoa(exit_status);
    free(curr->token);
    curr->token = exit_status_str;
}

void handle_exit_status_with_suffix(t_token *curr, t_shell *minishell, const char *suffix)
{
    char *exit_status_str;
    char *new_token;
    int exit_status;

    exit_status = minishell->last_return;
    exit_status_str = ft_itoa(exit_status);
    new_token = ft_strjoin(exit_status_str, suffix);
    free(curr->token);
    curr->token = new_token;
    free(exit_status_str);
}

void parse_value(t_token *token_lst, t_shell *minishell)
{
    t_token *curr;
    char *token;

    curr = token_lst;
    token = curr->token;

    if (token == NULL || token[0] != '$')
        return;
    if (ft_strcmp(token, "$") == 0)
        return;
    else if (ft_strcmp(token, "$?") == 0)
        handle_exit_status(curr, minishell);
    else if (ft_strncmp(token, "$?", 2) == 0)
        handle_exit_status_with_suffix(curr, minishell, token + 2);
    else
        handle_env_variable(curr, minishell);
}
