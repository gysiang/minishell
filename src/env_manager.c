/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:36:29 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/06 09:59:28 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(t_shell *minishell, const char *var)
{
    int i;
    size_t  var_len;

    i = 0;
    var_len = ft_strlen(var);
    while (minishell->env[i])
    {
        if (ft_strncmp(minishell->env[i], var, var_len) == 0 && minishell->env[i][var_len] == '=')
            return ft_strdup(&minishell->env[i][var_len + 1]);
        i++;
    }
    return (NULL);
}

int env_len(t_shell *minishell)
{
    int i;

    i = 0;
    while (minishell->env[i])
        i++;
    return (i);
}

int search_env_by_var(t_shell *minishell, const char *var)
{
    int i = 0;
    size_t var_len;

    var_len = ft_strlen(var);
    i = 0;
    while (minishell->env[i])
    {
        if (ft_strncmp(minishell->env[i], var, var_len) == 0 && minishell->env[i][var_len] == '=')
            return i;
        i++;
    }
    return (-1);
}

void  sort_env(t_shell *minishell)
{
    int i;
    int j;
    int environment_len;

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

//Need to split this into helper functions
void set_env(t_shell *minishell, const char *var, const char *value)
{
    int idx = search_env_by_var(minishell, var);
    size_t var_len = ft_strlen(var);
    size_t value_len = ft_strlen(value);
    char *new_entry = malloc(var_len + value_len + 2);
    if (!new_entry)
    {
        perror("Failed to allocate memory for new environment variable");
        return;
    }
    ft_strcpy(new_entry, var);
    new_entry[var_len] = '=';
    ft_strcpy(&new_entry[var_len + 1], value);
    if (idx != -1)
    {
        free(minishell->env[idx]);
        minishell->env[idx] = new_entry;
    }
    else
    {
        int current_length = env_len(minishell);
        if (minishell->env_size <= current_length + 1)
            env_realloc(minishell);
        minishell->env[current_length] = new_entry;
        minishell->env[current_length + 1] = NULL;
    }
}

void init_env(t_shell *minishell, char **envp)
{
	int i;
	int j;
	char *equal_sign;

	i = 0;
	j = 0;
	minishell->env = (char **)ft_calloc(BASE_ENV_SIZE, sizeof(char *));
	minishell->env_size = BASE_ENV_SIZE;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign && !ft_strnstr(envp[i], "_WORKSPACE_", equal_sign - &envp[i][0]))
		{
			if (j == minishell->env_size - 1)
				env_realloc(minishell);
			minishell->env[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
}