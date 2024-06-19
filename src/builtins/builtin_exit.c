/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/06/19 13:09:16 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_exit(t_shell *minishell, int exit_code)
{
	int	i;

	i = 0;
	while (i < minishell->process_count)
	{
		kill(minishell->process_ids[i], SIGTERM);
		waitpid(minishell->process_ids[i], NULL, WNOHANG);
		i++;
	}
	if (minishell->cmd_list != NULL)
	{
		free_tokenlst(minishell->cmd_list);
		minishell->cmd_list = NULL;
	}
	free_shell(minishell);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_code);
}
