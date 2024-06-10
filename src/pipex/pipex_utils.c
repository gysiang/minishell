/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:23:30 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/10 12:02:46 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_handler(int exit_code)
{
	if (exit_code == 1)
		ft_putstr_fd("infile cmd cmd outfile\n", 2);
	exit(EXIT_FAILURE);
}

int	open_file(const char *file, int mode)
{
	int	return_fd;

	if (mode == 0)
		return_fd = open(file, O_RDONLY, 0777);
	else
		return_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (return_fd == -1)
		exit_handler(1);
	return (return_fd);
}

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

char	*get_path(char *cmd, t_shell *minishell)
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
}

void	restore_fds(int input_fd, int output_fd)
{
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
}
