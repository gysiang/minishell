/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes_utils_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:46:06 by axlee             #+#    #+#             */
/*   Updated: 2024/06/09 12:41:01 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_special_env_variable(char *result, int *i, int *j, t_shell *minishell)
{
    char *expanded;

    expanded = ft_itoa(minishell->last_return);
    ft_strcpy(&result[*j], expanded);
    *j += ft_strlen(expanded);
    free(expanded);
    *i += 2;
}

void extract_variable_name(char *str, int *i, char **var_name, int *var_len)
{
    char *var_start;
    char *var_end;

    var_start = &str[*i + 1];
    var_end = var_start;
    while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
        var_end++;
    *var_len = var_end - var_start;
    *var_name = strndup(var_start, *var_len);
}

void handle_regular_env_variable(char *str, char *result, int *i, t_shell *minishell)
{
    int var_len;
    char *var_name;
    char *expanded;
    int j = *i;

    extract_variable_name(str, i, &var_name, &var_len);
    expanded = get_env_value(minishell, var_name);
    free(var_name);
    if (expanded)
    {
        ft_strcpy(&result[j], expanded);
        j += ft_strlen(expanded);
    }
    *i += var_len + 1;
    result[j] = '\0'; // Ensure null-termination
}

void handle_env_variable_expansion(char *str, char *result, int *i, t_shell *minishell)
{
    int j = *i;

    if (str[*i + 1] == '?')
        handle_special_env_variable(result, i, &j, minishell);
    else
        handle_regular_env_variable(str, result, i, minishell);
    result[j] = '\0'; // Ensure null-termination
}
