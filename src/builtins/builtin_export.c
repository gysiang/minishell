/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:45:07 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/23 17:08:13 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_var_name(const char *content)
{
    int len = 0;
    while (content[len] && content[len] != '=')
    {
        len++;
    }
    char *var_name = strndup(content, len);
    printf("Extracted variable name: %s\n", var_name); // Debugging print statement
    return var_name;
}

static int is_valid_identifier(const char *str)
{
    if (str == NULL || *str == '\0')
        return (0);
    if (!ft_isalpha(*str) && *str != '_')
        return (0);
    str++;
    while (*str)
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (0);
        str++;
    }
    return (1);
}

static void create_env_entry(char *dest, const char *var_name, const char *var_value)
{
    while (*var_name)
        *dest++ = *var_name++;
    *dest++ = '=';
    while (*var_value)
        *dest++ = *var_value++;
    *dest = '\0';
}

static int save_var(t_shell *minishell, char *content)
{
    char *var_name;
    char *var_value;
    int var_index;

    printf("Processing content: %s\n", content); // Debugging print statement

    if (ft_strchr(content, '=') == NULL)
    {
        if (!is_valid_identifier(content))
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(content, 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            return (1);
        }
        return (0);
    }

    var_name = get_var_name(content);
    if (!var_name || !is_valid_identifier(var_name))
    {
        ft_putstr_fd("minishell: export: `", 2);
        ft_putstr_fd(content, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        return (1);
    }
    var_value = ft_strchr(content, '=') + 1;
    printf("Extracted variable value: %s\n", var_value); // Debugging print statement

    if (*var_value == '\"' || *var_value == '\'')
    {
        char quote_type = *var_value;
        var_value++;
        char *end_quote = ft_strrchr(var_value, quote_type);
        if (end_quote)
        {
            *end_quote = '\0';
        }
    }
    printf("Processed variable value: %s\n", var_value); // Debugging print statement
    var_index = search_env(minishell, var_name);
    if (var_index == -1)
    {
        var_index = env_len(minishell);
    }

    char *new_entry = (char *)malloc(ft_strlen(var_name) + ft_strlen(var_value) + 2);
    if (!new_entry)
    {
        free(var_name);
        return (1);
    }
    ft_strcpy(new_entry, var_name);
    ft_strcat(new_entry, "=");
    ft_strcat(new_entry, var_value);
    create_env_entry(new_entry, var_name, var_value);
    printf("Setting environment variable: %s\n", new_entry); // Debugging print statement

    set_env_entry(minishell, new_entry, var_index);
    free(var_name);
    return (0);
}

int minishell_export(t_shell *minishell)
{
    t_token *tokens;
    t_token *current;
    int result;

    if (!minishell || !minishell->cmd_list)
    {
        printf("No command list provided.\n");
        return (0);
    }
    tokens = minishell->cmd_list;
    current = tokens->next;  // Start with the next token after 'export'
    if (!current)
    {
        print_vars(minishell);
        return (0);
    }
    result = 0;
    while (current)
    {
        printf("Processing token: %s\n", current->token); // Debugging print statement
        result = save_var(minishell, current->token);
        if (result != 0)
            return result;  // Return error code if save_var fails
        current = current->next;
    }
    return result;  // Return the last result or 0 if all variables processed successfully
}
