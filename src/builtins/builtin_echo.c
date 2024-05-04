/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/05/04 15:36:05 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}
