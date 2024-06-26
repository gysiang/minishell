/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:41:23 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/26 11:10:47 by gyong-si         ###   ########.fr       */
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

/**
 *
 * int	check_redirect_file(t_token *curr)
{
	if (curr->next && curr->next->next && curr->next->type == T_FILE
		&& curr->next->next->type == T_IDENTIFIER && !curr->next->next->next)
	{
		return (1);
	}
	return (0);
}
 */
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
	//printf("no of arg : %d\n", i);
	//printf("curr : %s\n", curr->token);
	//printf("check redirect file: %d\n", check_redirect_file(curr->next));
	if (check_redirect_file(curr))
		num += 1;
	//printf("num %d\n", i);
	while (curr != NULL && num > 0)
	{
		curr = curr->next;
		num--;
	}
	return (curr);
}
