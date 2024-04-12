/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/04/12 10:48:22 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_echo(t_shell *minishell, t_cmd *cmd)
{
	(void)minishell;
	t_bool	print_newline;
	int	i;

	i = 1;
	print_newline = TRUE;
	if (cmd->argv[1] && cmd->argv[1][0] == '-' && cmd->argv[1][1] == 'n' && cmd->argv[1][2] == '\0')
	{
		print_newline = FALSE;
		i++;
	}
	if (cmd->argv[i] != NULL)
	{
		while (cmd->argv[i])
		{
			ft_putstr(cmd->argv[i]);
			if (cmd->argv[i + 1])
				ft_putchar(' ');
			i++;
		}
	}
	if (print_newline)
		ft_putchar('\n');
	return (0);
}