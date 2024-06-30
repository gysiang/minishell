/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:09:33 by axlee             #+#    #+#             */
/*   Updated: 2024/06/30 20:25:24 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_shell *minishell, const char *var, int return_empty)
{
	int		i;
	size_t	var_len;

	var_len = ft_strlen(var);
	if (var_len == 0)
		return (ft_strdup("$"));
	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], var, var_len) == 0
			&& minishell->env[i][var_len] == '=')
		{
			return (ft_strdup(&minishell->env[i][var_len + 1]));
		}
		i++;
	}
	if (return_empty)
		return (ft_strdup(""));
	return (NULL);
}

int	env_len(t_shell *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i])
		i++;
	return (i);
}

int	search_env_by_var(t_shell *minishell, const char *var)
{
	int		i;
	size_t	var_len;

	var_len = ft_strlen(var);
	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], var, var_len) == 0
			&& minishell->env[i][var_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
