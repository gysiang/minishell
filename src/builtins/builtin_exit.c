/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/06/09 16:46:49 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_exit(t_shell *minishell)
{
	int i;

	i = 0;
	while (i < minishell->process_count)
	{
		kill(minishell->process_ids[i], SIGTERM);
		waitpid(minishell->process_ids[i], NULL, WNOHANG);
		i++;
	}
	free_tokenlst(minishell->cmd_list);
	free_shell(minishell);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(0);
}
