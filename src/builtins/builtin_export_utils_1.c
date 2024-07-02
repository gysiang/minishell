/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:10:31 by axlee             #+#    #+#             */
/*   Updated: 2024/07/02 13:34:13 by gyongsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_realloc(t_shell *minishell)
{
	char	**new_env;
	int		old_size;
	int		i;

	old_size = minishell->env_size;
	minishell->env_size *= 2;
	new_env = (char **)ft_realloc(minishell->env, minishell->env_size
			* sizeof(char *));
	if (new_env == NULL)
	{
		ft_putendl_fd("minishell: memory allocation failed", 2);
		free_and_exit(minishell, 1);
	}
	minishell->env = new_env;
	i = old_size;
	while (i < minishell->env_size)
	{
		minishell->env[i] = NULL;
		i++;
	}
}

void	print_vars(t_shell *minishell)
{
	int		i;
	char	*eq_sign;

	i = 0;
	sort_env(minishell);
	while (i < env_len(minishell))
	{
		eq_sign = ft_strchr(minishell->env[i], '=');
		if (eq_sign)
		{
			*eq_sign = '\0';
			printf("%s=%s\n", minishell->env[i], eq_sign + 1);
			*eq_sign = '=';
		}
		else
			printf("declare -x %s\n", minishell->env[i]);
		i++;
	}
}

char	*string_concat(char **strings, char *joined, int start_index)
{
	char	*temp;
	int		i;
	size_t	new_len;

	i = start_index;
	while (strings[i])
	{
		new_len = ft_strlen(joined) + ft_strlen(strings[i]) + 1;
		if (i > start_index)
			new_len++;
		temp = (char *)ft_realloc(joined, new_len);
		if (!temp)
		{
			free(joined);
			return (NULL);
		}
		joined = temp;
		strcat(joined, strings[i]);
		if (strings[i + 1])
			strcat(joined, " ");
		i++;
	}
	return (joined);
}

char	*join_from_index(char **cmd, int start_index)
{
	char	*joined;
	char	*result;

	joined = (char *)malloc(1);
	if (!joined)
		return (NULL);
	joined[0] = '\0';
	result = string_concat(cmd, joined, start_index);
	return (result);
}
