/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:02:34 by axlee             #+#    #+#             */
/*   Updated: 2024/06/30 20:21:43 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_two_tabs(char **tab1, char **tab2)
{
	ft_free_tab(tab1);
	ft_free_tab(tab2);
}

static void	initialize_path_components(char *cmd, t_shell *minishell,
		char ***all_path, char ***s_cmd)
{
	char	*env_val;

	env_val = get_env_value(minishell, "PATH", 1);
	*all_path = ft_split(env_val, ':');
	free(env_val);
	*s_cmd = ft_split(cmd, ' ');
}

static char	*search_executable(char **all_path, char **s_cmd)
{
	int		i;
	char	*exec;
	char	*path_part;

	i = -1;
	while (all_path[++i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			return (exec);
		}
		free(exec);
	}
	return (NULL);
}

char	*get_path(char *cmd, t_shell *minishell)
{
	char	**all_path;
	char	**s_cmd;
	char	*exec;

	initialize_path_components(cmd, minishell, &all_path, &s_cmd);
	exec = search_executable(all_path, s_cmd);
	if (exec)
	{
		ft_free_two_tabs(s_cmd, all_path);
		return (exec);
	}
	ft_free_two_tabs(all_path, s_cmd);
	return (NULL);
}
