/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:09:33 by axlee             #+#    #+#             */
/*   Updated: 2024/06/25 23:45:20 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_1(t_token *curr, t_shell *minishell)
{
	if (ft_strncmp(curr->token, "cd", 2) == 0)
	{
		minishell_cd(minishell);
		return (1);
	}
	if (ft_strncmp(curr->token, "echo", 4) == 0)
	{
		minishell_echo(curr, minishell);
		return (1);
	}
	if (ft_strncmp(curr->token, "env", 3) == 0)
	{
		minishell_env(minishell);
		return (1);
	}
	return (0);
}

int	execute_builtin_2(t_token *curr, t_shell *minishell)
{
	if (ft_strncmp(curr->token, "exit", 4) == 0)
	{
		handle_exit_command(curr, minishell);
		return (1);
	}
	if (ft_strncmp(curr->token, "export", 6) == 0)
	{
		minishell_export(minishell);
		return (1);
	}
	if (ft_strncmp(curr->token, "unset", 5) == 0)
	{
		minishell_unset(minishell);
		return (1);
	}
	return (0);
}

int	other_cmds(t_token *curr, t_shell *minishell)
{
	(void)minishell;
	if (ft_strcmp(curr->token, "pwd") == 0)
	{
		minishell_pwd();
		return (1);
	}
	if (ft_strcmp(curr->token, "history") == 0)
	{
		print_history();
		return (1);
	}
	if (ft_strcmp(curr->token, "history -c") == 0)
	{
		clear_history();
		return (1);
	}
	return (0);
}
