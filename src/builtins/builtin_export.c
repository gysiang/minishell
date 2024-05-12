/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:45:07 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/12 14:17:41 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char *get_var_name(char *cmd)
{
	char *equal_pos;
	equal_pos = ft_strchr(cmd, '=');
	if (equal_pos)
		return ft_substr(cmd, 0, equal_pos - cmd);
	return (NULL);
}
/***
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
} **/

void env_realloc(t_shell *minishell)
{
	char **new_env;
	int	old_size;

	old_size = minishell->env_size;
	minishell->env_size *= 2;
	new_env = (char **)realloc(minishell->env, minishell->env_size * sizeof(char *));
	if (new_env == NULL)
	{
		ft_putendl_fd("minishell: memory allocation failed", 2);
		free_and_exit(minishell, 1);
	}
	minishell->env = new_env;
	//printf("Environment reallocated. New size: %d\n", minishell->env_size);
	int  i = old_size;
	while (i < minishell->env_size)
	{
		minishell->env[i] = NULL;
		i++;
	}
	//printf("Environment initialization complete \n");
}

static int is_valid_identifier(const char *str)
{
    if (str == NULL || *str == '\0' || ft_isdigit(*str))
	{
		return (0);
	}
	/***
    while (*str)
    {
        if (!ft_isalnum(*str))
		{
			printf("not alphabet\n");
            return (0);
		}
        str++;
    }
	**/
    return (1);
}

static int save_var(t_shell *minishell, char *content)
{
	char *var_name;
	int var_index;

	printf("inside savevar\n");
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
	//printf("var name %s\n", var_name);
	var_index = search_env(minishell, var_name);
	//printf("var id %d\n", var_index);
	//free(var_name);
	// cannot find the variable, adding the varable to end of list
	if (var_index == -1)
		var_index = env_len(minishell);
	//printf("setting new id: %d\n", var_index);
	if (var_index == minishell->env_size)
	{
		printf("Environment size reached. Reallocating...\n");
		env_realloc(minishell);
	}
	//free(minishell->env[var_index]);
	minishell->env[var_index] = ft_strdup(content);
	//printf("Variable '%s' saved at index %d\n", content, var_index);
	//printf("New value: '%s'\n", minishell->env[var_index]);
	return (0);
}

void print_vars(t_shell *minishell)
{
	int i;

	i = 0;
	while (i < env_len(minishell))
	{
		printf("Variable %d: %s\n", i, minishell->env[i]);
		i++;
	}
}

static char *join_from_index(char **cmd, int start_index)
{
	char	*joined;
	char	*temp;
	int		i;
	size_t new_len;

	joined = (char *)malloc(1);
	if (!joined)
		return NULL;
	joined[0] = '\0';
	i = start_index;
	while (cmd[i])
	{
		new_len = ft_strlen(joined) + ft_strlen(cmd[i]) + 1;
		temp = (char *)realloc(joined, new_len);
		if (!temp)
		{
			free(joined);
			return (NULL);
		}
		joined = temp;
		ft_strcat(joined, cmd[i]);
		if (cmd[i + 1])
			ft_strcat(joined, " ");
		i++;
	}
	return (joined);
}

int minishell_export(t_shell *minishell)
{
	t_token *token;
	char	**cmd;
	char *joined;

	token = minishell->cmd_list;
	if (!token)
	{
		print_vars(minishell);
		return (0);
	}
	cmd = ft_split(token->token, ' ');
	joined = join_from_index(cmd, 1);
	if (joined)
	{
		save_var(minishell, joined);
	}
	free(joined);
	//sort_env(minishell);
	return (0);
}
