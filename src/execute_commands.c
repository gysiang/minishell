/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:09:33 by axlee             #+#    #+#             */
/*   Updated: 2024/05/31 09:49:40 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *s)
{
	if (!ft_strncmp(s, "cd", 2) || !ft_strcmp(s, "echo")
		|| !ft_strncmp(s, "env", 3) || !ft_strcmp(s, "pwd")
		|| !ft_strncmp(s, "export", 6) || !ft_strncmp(s, "unset", 5)
		|| !ft_strcmp(s, "history") || !ft_strcmp(s, "history -c")
		|| !ft_strcmp(s, "exit"))
	{
		return (1);
	}
	return (0);
}

int	execute_builtin_1(t_token *curr, t_shell *minishell)
{
	char	*s;

	if (curr == NULL)
		return (0);
	s = curr->token;
	if (ft_strncmp(s, "cd", 2) == 0)
	{
		minishell_cd(minishell);
		return (1);
	}
	if (ft_strncmp(s, "echo", 4) == 0)
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

static int count_tokens(t_shell *minishell)
{
	int	count;
	t_token *token;

	count = 0;
	token = minishell->cmd_list;
	while (token != NULL)
    {
        count++;
        token = token->next;
    }
	printf("Total tokens: %d\n", count);
	return (count);
}

int execute_builtin_2(t_token *curr, t_shell *minishell)
{
	int	count;

	count = 0;
    if (ft_strncmp(curr->token, "exit", 4) == 0)
    {
		count = count_tokens(minishell);
        if (count > 2)
        {
            minishell_error_msg("exit", 43);
            return 1;
        }
        minishell_exit(minishell);
        return 1;
    }
    else if (ft_strncmp(curr->token, "export", 6) == 0)
    {
        minishell_export(minishell);
        return 1;
    }
    else if (ft_strncmp(curr->token, "unset", 5) == 0)
    {
        minishell_unset(minishell);
        return 1;
    }
    return 0;
}

int	other_cmds(t_token *curr, t_shell *minishell)
{
	char	*s;

	if (curr == NULL)
		return (0);
	s = curr->token;
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
