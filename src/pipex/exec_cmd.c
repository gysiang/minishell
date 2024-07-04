/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:59:49 by axlee             #+#    #+#             */
/*   Updated: 2024/07/04 13:39:57 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_cmd(t_token *curr, t_shell *minishell)
{
	char	**s_cmd;
	char	*path;

	if (check_command(curr->token, minishell))
		return ;
	s_cmd = get_command_array(curr->token, minishell);
	if (!s_cmd || !s_cmd[0] || ft_strlen(s_cmd[0]) == 0)
	{
		minishell->last_return = minishell_error_msg(curr->token, 42);
		if (s_cmd)
			ft_free_tab(s_cmd);
		return ;
	}
	path = get_command_path(s_cmd, minishell);
	if (!path)
	{
		if (minishell->last_return != 126) // If it's not a directory error
			minishell->last_return = minishell_error_msg(curr->token, 42);
		ft_free_tab(s_cmd);
		return ;
	}
	if (ft_strncmp(curr->token, "expr ", 5) == 0)
		handle_expr_command(curr, minishell);
	else if (execve(path, s_cmd, minishell->env) == -1)
		handle_execve_failure(s_cmd, minishell, errno);
	ft_free_tab(s_cmd);
	free(path);
}
