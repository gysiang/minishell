/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:09:33 by axlee             #+#    #+#             */
/*   Updated: 2024/06/16 11:31:52 by axlee            ###   ########.fr       */
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

/*char	*get_env_value(t_shell *minishell, const char *var)
{
	int		i;
	size_t	var_len;
	int		i;
	size_t	var_len;
	int		i;

	var_len = ft_strlen(var);
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
	return (ft_strdup(""));
}*/
// If return NULL, it will output echo $ as $ but will also output echo $TEST
// as $TEST
/*char	*get_env_value(t_shell *minishell, const char *var)
{
	var_len = ft_strlen(var);
	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], var, var_len) == 0
			&& minishell->env[i][var_len] == '=')
			return (ft_strdup(&minishell->env[i][var_len + 1]));
		i++;
	}
	return (NULL);
}*/
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
