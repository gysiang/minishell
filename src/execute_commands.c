/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:09:33 by axlee             #+#    #+#             */
/*   Updated: 2024/05/18 09:21:09 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *s)
{
	if (!ft_strncmp(s, "cd", 2) || !ft_strcmp(s, "echo")
		|| !ft_strncmp(s, "env", 3) || !ft_strcmp(s, "pwd")
		|| !ft_strncmp(s, "export", 6) || !ft_strncmp(s, "unset", 5)
		|| !ft_strcmp(s, "history") || !ft_strcmp(s, "history -c"))
	{
		return (1);
	}
	return (0);
}

int	execute_builtin_1(t_shell *minishell)
{
	char	*s;

	s = minishell->cmd_list->token;
	if (minishell->cmd_list == NULL)
		return (0);
	if (ft_strncmp(s, "cd", 2) == 0)
	{
		minishell_cd(minishell);
		return (1);
	}
	if (ft_strcmp(s, "echo") == 0)
	{
		minishell_echo(minishell);
		return (1);
	}
	if (ft_strncmp(s, "env", 3) == 0)
	{
		minishell_env(minishell);
		return (1);
	}
	return (0);
}

int	execute_builtin_2(t_shell *minishell)
{
	char	*s;

	s = minishell->cmd_list->token;
	if (minishell->cmd_list == NULL)
		return (0);
	if (ft_strncmp(s, "exit", 4) == 0)
	{
		minishell_exit(minishell);
		return (1);
	}
	if (ft_strncmp(s, "export", 6) == 0)
	{
		printf("calling export\n");
		minishell_export(minishell);
		return (1);
	}
	if (ft_strncmp(s, "unset", 5) == 0)
	{
		printf("calling unset\n");
		minishell_unset(minishell);
		return (1);
	}
	return (0);
}

int	other_cmds(t_shell *minishell)
{
	char	*s;

	s = minishell->cmd_list->token;
	if (minishell->cmd_list == NULL)
		return (0);
	if (ft_strcmp(s, "pwd") == 0)
	{
		minishell_pwd(minishell);
		return (1);
	}
	if (ft_strcmp(s, "history") == 0)
	{
		print_history();
		return (1);
	}
	if (ft_strcmp(s, "history -c") == 0)
	{
		clear_history();
		return (1);
	}
	return (0);
}
