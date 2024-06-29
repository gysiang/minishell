/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:02:34 by axlee             #+#    #+#             */
/*   Updated: 2024/06/29 23:02:23 by gyong-si         ###   ########.fr       */
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

// OPTION_1
/*static char	*try_exec_path(char **all_path, char **s_cmd)
{
	int		i;
	char	*exec;
	char	*path_part;

	i = 0;
	while (all_path[i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			return (exec);
		}
		free(exec);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_shell *minishell)
{
	char	*exec;
	char	**all_path;
	char	**s_cmd;
	char	*env_path;

	env_path = get_env_value(minishell, "PATH");  // Use custom get_env_value
	if (env_path == NULL)
		return (NULL);
	all_path = ft_split(env_path, ':');
	free(env_path);  // Free the memory allocated by get_env_value
	s_cmd = ft_split(cmd, ' ');
	exec = try_exec_path(all_path, s_cmd);
	ft_free_tab(all_path);
	ft_free_tab(s_cmd);
	return (exec);
}*/
void	ft_free_two_tabs(char **tab1, char **tab2)
{
	ft_free_tab(tab1);
	ft_free_tab(tab2);
}

// OPTION_2 (PREFFERED)
char	*get_path(char *cmd, t_shell *minishell)
{
	int		i;
	char	*exec;
	char	*path_part;
	char	**all_path;
	char	**s_cmd;

	(void)minishell;
	i = -1;
	all_path = ft_split(get_env_value(minishell, "PATH", 1), ':');
	i = -1;
	s_cmd = ft_split(cmd, ' ');
	while (all_path[++i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_two_tabs(s_cmd, all_path);
			return (exec);
		}
		free(exec);
	}
	ft_free_two_tabs(all_path, s_cmd);
	return (NULL);
}

// OPTION_3
/*char	*get_path(char *cmd, t_shell *minishell)
{
	int		i;
	char	*exec;
	char	*path_part;
	char	**all_path;
	char	**s_cmd;

	i = -1;
	all_path = ft_split(get_env_value(minishell, "PATH"), ':');
	s_cmd = ft_split(cmd, ' ');
	while (all_path[++i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			ft_free_tab(all_path);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(all_path);
	ft_free_tab(s_cmd);
	return (NULL);
}*/
