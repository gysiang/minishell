/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:09:33 by axlee             #+#    #+#             */
/*   Updated: 2024/06/14 15:33:31 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// If return (strdup == "", it will output echo $TEST as empty string but further issues at the back)
/*char	*get_env_value(t_shell *minishell, const char *var)
{
	int		i;
	size_t	var_len;
	int		i;
	size_t	var_len;
	char	*value;

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
	// Return an empty string if the environment variable is not found
	return (ft_strdup(""));
}*/

char	*get_env_value(t_shell *minishell, const char *var)
{
	int		i;
	size_t	var_len;
	char	*value;

	value = NULL;
	var_len = ft_strlen(var);
	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], var, var_len) == 0
			&& minishell->env[i][var_len] == '=')
		{
			value = ft_strdup(&minishell->env[i][var_len + 1]);
			if (value == NULL)
			{
				// Handle memory allocation failure
				return (NULL);
			}
			return (value);
		}
		i++;
	}
	return (NULL);
}

// If return NULL, it will output echo $ as $ but will also output echo $TEST as $TEST
/*char	*get_env_value(t_shell *minishell, const char *var)
{
	int		i;
	size_t	var_len;
	int		i;

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
	int		i;

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
