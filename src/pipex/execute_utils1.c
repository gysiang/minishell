/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:41:23 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/22 00:16:28 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_previous_fd_to_stdin(t_shell *minishell)
{
	if (minishell->prev_fd != -1)
	{
		dup2(minishell->prev_fd, STDIN_FILENO);
		close(minishell->prev_fd);
	}
}

void	load_previous_fd_to_stdout(t_shell *minishell)
{
	if (minishell->prev_fd != -1)
	{
		dup2(minishell->prev_fd, STDOUT_FILENO);
		close(minishell->prev_fd);
	}
}

void	update_curr_pointer(t_token **curr, int flag)
{
	if (!flag)
		*curr = (*curr)->next->next;
	else
		*curr = (*curr)->next->next->next->next;
}
