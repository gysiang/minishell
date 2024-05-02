/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/05/02 14:04:59 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
int	minishell_echo(t_shell *minishell, t_cmd *cmd)
{
	int	print_newline;
	int	i;

	(void)minishell;
	i = 1;
	print_newline = 1;
	if (cmd->argv[1] && cmd->argv[1][0] == '-' && cmd->argv[1][1] == 'n' && cmd->argv[1][2] == '\0')
	{
		print_newline = 0;
		i++;
	}
	if (cmd->argv[i] != NULL)
	{
		while (cmd->argv[i])
		{
			ft_putstr_fd(cmd->argv[i], 1);
			if (cmd->argv[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (print_newline == 1)
		ft_putchar_fd('\n', 1);
	return (0);
} **/

int	minishell_echo(t_shell *minishell)
{
	int	print_newline;
	t_token	*curr_token;

	curr_token = minishell->cmd_list;
	print_newline = 1;
	if (ft_strcmp(curr_token->token, "echo n") == 0)
	{
		print_newline = 0;
		curr_token = curr_token->next;
	}
	else if (ft_strcmp(curr_token->token, "echo") == 0)
		curr_token = curr_token->next;
	if (curr_token != NULL)
	{
		printf("%s",curr_token->token);
	}
	if (print_newline == 1)
		ft_putchar_fd('\n', 1);
	return (0);
}
