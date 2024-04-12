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

int	minishell_unset(t_shell *minishell, t_cmd *cmd)
{
	int	i;
	int	var_index;

	i = 1;
	while (cmd->argv[i])
	{
		var_index = search_env(minishell, cmd->argv[i]); // Need to write the function to search environment;
		if (var_index >= 0)
		{
			free(minishell->env[var_index]);
			shift_env_entries(minishell, var_index);
		}
		i++;
	}
	return (0);
}
