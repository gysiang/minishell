/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:58:24 by axlee             #+#    #+#             */
/*   Updated: 2024/06/19 15:12:50 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *s)
{
	if (!ft_strncmp(s, "cd", 2) || !ft_strcmp(s, "echo") || !ft_strncmp(s,
			"env", 3) || !ft_strcmp(s, "pwd") || !ft_strncmp(s, "export", 6)
		|| !ft_strncmp(s, "unset", 5) || !ft_strcmp(s, "history")
		|| !ft_strcmp(s, "history -c") || !ft_strcmp(s, "exit"))
	{
		return (1);
	}
	return (0);
}

int	count_tokens(t_shell *minishell)
{
	int		count;
	t_token	*token;

	count = 0;
	token = minishell->cmd_list;
	while (token != NULL)
	{
		count++;
		token = token->next;
	}
	return (count);
}

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	handle_exit_command(t_token *curr, t_shell *minishell)
{
	int	count;
	int	exit_code;

	count = count_tokens(minishell);
	if (count > 2)
	{
		minishell_error_msg("exit", 43);
		minishell->last_return = 1;
		return ;
	}
	exit_code = 0;
	if (curr->next && curr->next->token)
	{
		if (!is_numeric(curr->next->token))
		{
			minishell_error_msg("exit", 44);
			minishell->last_return = 2;
			return ;
		}
		exit_code = ft_atoi(curr->next->token);
	}
	minishell_exit(minishell, exit_code);
}
