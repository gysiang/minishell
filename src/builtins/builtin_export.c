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

static char	*get_var_name(char *cmd)
{
	char	*equal_pos;

	equal_pos = ft_strchr(cmd, '=');
	if (equal_pos)
		return (ft_substr(cmd, 0, equal_pos - cmd));
	return (NULL);
}

static int	is_valid_identifier(const char *str)
{
	if (str == NULL || *str == '\0' || ft_isdigit(*str))
		return (0);
	return (1);
}

static int	save_var(t_shell *minishell, char *content)
{
	char	*var_name;
	int		var_index;

	if (!is_valid_identifier(content))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(content, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	var_name = get_var_name(content);
	if (!var_name)
		return (0);
	var_index = search_env(minishell, var_name);
	if (var_index == -1)
		var_index = env_len(minishell);
	if (var_index == minishell->env_size)
		env_realloc(minishell);
	minishell->env[var_index] = ft_strdup(content);
	return (0);
}

int minishell_export(t_shell *minishell)
{
	t_token	*tokens;
	t_token	*current;
	int	result;

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
        result = save_var(minishell, current->token);
        if (result != 0)
            return result;  // Return error code if save_var fails
        current = current->next;
    }
    return result;  // Return the last result or 0 if all variables processed successfully
}
