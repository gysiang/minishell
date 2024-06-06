/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:21:39 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/06 23:23:11 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command(char *cmd, t_shell *minishell)
{
	if (!cmd || !minishell)
	{
		printf("Invalid command or shell context\n");
		ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
		minishell->last_return = 1;
		exit(1);
	}
	if (ft_strncmp(cmd, "$?", 2) == 0)
	{
		printf("Handling special case for last return status\n");
		printf("%d\n", minishell->last_return);
		minishell->last_return = 0;
		exit(1);
	}
	return (0);
}

char	**get_command_array(char *cmd, t_shell *minishell)
{
	char **s_cmd;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
	{
		printf("Failed to split command string\n");
		ft_putstr_fd("Failed to split command\n", STDERR_FILENO);
		minishell->last_return = 1;
		exit(1);
	}
	return (s_cmd);
}

char	*get_command_path(char **s_cmd, t_shell *minishell)
{
	int		return_code;
	char	*path;

	return_code = 0;
	if (s_cmd[0][0] == '/' || s_cmd[0][0] == '.')
		path = s_cmd[0];
	else
		path = get_path(s_cmd[0], minishell);
	if (!path)
	{
		printf("Command not found: %s\n", s_cmd[0]);
		return_code = minishell_error_msg(s_cmd[0], 42);
		minishell->last_return = return_code;
		exit(1);
	}
	return (path);
}

void	load_previous_fd(t_shell *minishell)
{
	if (minishell->prev_fd != -1)
	{
		dup2(minishell->prev_fd, STDIN_FILENO);
		close(minishell->prev_fd);
	}
}

void	exec_cmd(t_token *curr, t_shell *minishell)
{
	char	**s_cmd;
	char	*path;
	int	return_code;

	check_command(curr->token, minishell);
	s_cmd = get_command_array(curr->token, minishell);
	path = get_command_path(s_cmd, minishell);
	if (execve(path, s_cmd, minishell->env) == -1)
	{
		printf("execve failed: %s\n", strerror(errno));
		return_code = minishell_error_msg(s_cmd[0], errno);
		minishell->last_return = return_code;
	}
	ft_free_tab(s_cmd);
}
