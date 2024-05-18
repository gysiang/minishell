/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:10:31 by axlee             #+#    #+#             */
/*   Updated: 2024/05/17 12:29:18 by axlee            ###   ########.fr       */
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
	new_env = (char **)realloc(minishell->env, minishell->env_size
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
	int	i;

	i = 0;
	while (i < env_len(minishell))
	{
		printf("Variable %d: %s\n", i, minishell->env[i]);
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
		new_len = ft_strlen(joined) + ft_strlen(strings[i]);
		if (i > start_index)
			new_len += 1;
		temp = (char *)realloc(joined, new_len);
		if (!temp)
		{
			free(joined);
			return (NULL);
		}
		joined = temp;
		ft_strcat(joined, strings[i]);
		if (strings[i + 1])
			ft_strcat(joined, " ");
		i++;
	}
	return (joined);
}

char	*join_from_index(char **cmd, int start_index)
{
	char	*joined;

	joined = (char *)malloc(1);
	if (!joined)
		return (NULL);
	joined[0] = '\0';
	return (string_concat(cmd, joined, start_index));
}