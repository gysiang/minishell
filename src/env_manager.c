/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:36:29 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/17 14:26:53 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(t_shell *minishell)
{
	int	i;
	int	j;
	int	environment_len;

	i = 0;
	environment_len = env_len(minishell);
	while (i < environment_len - 1)
	{
		j = 0;
		while (j < environment_len - i - 1)
		{
			if (ft_strccmp(minishell->env[j], minishell->env[j + 1], '=') > 0)
				ft_strswap(&minishell->env[j], &minishell->env[j + 1]);
			j++;
		}
		i++;
	}
}

static void	set_env_entry(t_shell *minishell, char *new_entry, int idx)
{
	int	current_length;

	if (idx != -1)
	{
		free(minishell->env[idx]);
		minishell->env[idx] = new_entry;
	}
	else
	{
		current_length = env_len(minishell);
		if (minishell->env_size <= current_length + 1)
			env_realloc(minishell);
		minishell->env[current_length] = new_entry;
		minishell->env[current_length + 1] = NULL;
	}
}

void	set_env(t_shell *minishell, const char *var, const char *value)
{
	int		idx;
	size_t	var_len;
	size_t	value_len;
	char	*new_entry;

	idx = search_env_by_var(minishell, var);
	var_len = ft_strlen(var);
	value_len = ft_strlen(value);
	new_entry = malloc(var_len + value_len + 2);
	if (!new_entry)
	{
		perror("Failed to allocate memory for new environment variable");
		return ;
	}
	ft_strcpy(new_entry, var);
	new_entry[var_len] = '=';
	ft_strcpy(&new_entry[var_len + 1], value);
	set_env_entry(minishell, new_entry, idx);
}

void	init_env(t_shell *minishell, char **envp)
{
	int		i;
	int		j;
	char	*equal_sign;

	i = 0;
	j = 0;
	minishell->env = (char **)ft_calloc(BASE_ENV_SIZE, sizeof(char *));
	minishell->env_size = BASE_ENV_SIZE;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign && !ft_strnstr(envp[i], "_WORKSPACE_", equal_sign
				- &envp[i][0]))
		{
			if (j == minishell->env_size - 1)
				env_realloc(minishell);
			minishell->env[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
}
