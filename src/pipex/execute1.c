/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:10:53 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/11 16:37:21 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command_with_redir(t_token *curr, t_shell *minishell)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		load_previous_fd(minishell);
		if (handle_redirection(minishell, curr->next))
			exec_cmd(curr, minishell);
	}
	else
	{
		signal(SIGINT, sigint_handler1);
		minishell->process_ids[minishell->process_count++] = pid;
		if (minishell->prev_fd != -1)
			close(minishell->prev_fd);
	}
}
