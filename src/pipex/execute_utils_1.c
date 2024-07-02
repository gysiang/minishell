/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:21:39 by gyong-si          #+#    #+#             */
/*   Updated: 2024/07/03 00:28:52 by gyong-si         ###   ########.fr       */
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
	if (ft_strcmp(cmd, "$") == 0)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		minishell->last_return = 127;
		exit(127);
	}
	return (0);
}

char	*get_command_path(char **s_cmd, t_shell *minishell)
{
	char		*path;
	struct stat	statbuf;

	if (s_cmd[0][0] == '/' || s_cmd[0][0] == '.')
		path = s_cmd[0];
	else
		path = get_path(s_cmd[0], minishell);
	if (!path)
	{
		minishell->last_return = minishell_error_msg(s_cmd[0], 42);
		return (NULL);
	}
	if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		minishell->last_return = minishell_error_msg(s_cmd[0], EISDIR);
		return (NULL);
	}
	return (path);
}

static void	handle_execve_failure(char **s_cmd, t_shell *minishell,
		int error_code)
{
	int	return_code;

	return_code = minishell_error_msg(s_cmd[0], error_code);
	minishell->last_return = return_code;
	ft_free_tab(s_cmd);
	exit(return_code);
}

static void	handle_expr_command(t_token *curr, t_shell *minishell)
{
	char	**args;

	args = ft_split(curr->token, ' ');
	execve("/usr/bin/expr", args, minishell->env);
	ft_free_tab(args);
}

int	exec_cmd(t_token *curr, t_shell *minishell)
{
	char	**s_cmd;
	char	*path;

	if (check_command(curr->token, minishell))
		return (1);
	s_cmd = get_command_array(curr->token, minishell);
	if (!s_cmd || !s_cmd[0] || ft_strlen(s_cmd[0]) == 0)
	{
		minishell->last_return = 0;
		if (s_cmd)
			ft_free_tab(s_cmd);
		return (1);
	}
	path = get_command_path(s_cmd, minishell);
	if (!path)
	{
		ft_free_tab(s_cmd);
		return (1);
	}
	if (ft_strncmp(curr->token, "expr ", 5) == 0)
		handle_expr_command(curr, minishell);
	else if (execve(path, s_cmd, minishell->env) == -1)
	{
		handle_execve_failure(s_cmd, minishell, errno);
		return (1);
	}
	ft_free_tab(s_cmd);
	return (0);
}
