/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:39:54 by axlee             #+#    #+#             */
/*   Updated: 2024/04/12 13:01:42 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shift_env_entries(t_shell *minishell, int start_index)
{
	while (minishell->env[start_index + 1])
	{
		minishell->env[start_index] = minishell->env[start_index + 1];
		start_index++;
	}
	minishell->env[start_index] = NULL;
}

int	search_env(t_shell *minishell, char *var)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strcmp(minishell->env[i], var) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	is_valid_var_name(char *var_name)
{
	int	i;

	i = 1;
	if (var_name || !var_name[0])
		return (0);
	if (!ft_isalpha(var_name[0]) && var_name[0] != '_')
		return (0);
	i = 1;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_' )
			return (0);
		i++;
	}
	return (1);
}

int minishell_unset(t_shell *minishell)
{
    t_token *token = minishell->cmd_list->next;
    int var_index;

    while (token)
    {
        if (!is_valid_var_name(token->token))
        {
            ft_putstr_fd("minishell: unset: '", 2);
            ft_putstr_fd(token->token, 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
        }
        else
        {
            var_index = search_env(minishell, token->token);
            if (var_index >= 0)
            {
                free(minishell->env[var_index]);
                shift_env_entries(minishell, var_index);
            }
        }
        token = token->next;
    }
    return 0;
}