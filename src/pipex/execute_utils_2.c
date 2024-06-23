/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:41:23 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/23 15:33:23 by axlee            ###   ########.fr       */
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

t_token	*update_curr_pointer(t_token *curr, int flag, int i)
{
	int	num;

	num = 0;
	if (flag <= 1)
		num = i + 1;
	else if (flag == 2)
		num = 4;
	else
		num = 6;
	while (curr != NULL && num > 0)
	{
		curr = curr->next;
		num--;
	}
	return (curr);
}
