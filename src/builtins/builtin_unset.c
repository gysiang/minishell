/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:39:54 by axlee             #+#    #+#             */
/*   Updated: 2024/05/24 15:31:59 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_valid_identifier(const char *str)
{
    if (str == NULL || *str == '\0' || ft_isdigit(*str))
        return (0);
    return (1);
}
int	search_env(t_shell *minishell, char *var)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void shift_env_entries(t_shell *minishell, int index)
{
    if (index < 0 || index >= env_len(minishell))
        return;
    while (minishell->env[index] != NULL)
    {
        free(minishell->env[index]);
        minishell->env[index] = minishell->env[index + 1];
        index++;
    }
}

static void unset_variable(t_shell *minishell, char *var_name)
{
    int var_index;

    if (!is_valid_identifier(var_name))
    {
        printf("minishell: unset: '%s': not a valid identifier\n", var_name);
        return;
    }
    var_index = search_env(minishell, var_name);
    if (var_index >= 0)
    {
        shift_env_entries(minishell, var_index);
        printf("minishell: unset: removed '%s'\n", var_name);
    }
    else
        printf("minishell: unset: '%s' not found in environment\n", var_name);
}

int minishell_unset(t_shell *minishell)
{
    t_token *current;

    if (!minishell || !minishell->cmd_list)
    {
        printf("No command list provided.\n");
        return (0);
    }
    current = minishell->cmd_list->next;  // Start with the next token after 'unset'
    while (current)
    {
        unset_variable(minishell, current->token);
        current = current->next;
    }
    return (0);
}
