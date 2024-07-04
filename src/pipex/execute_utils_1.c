/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:41:23 by gyong-si          #+#    #+#             */
/*   Updated: 2024/07/04 12:57:38 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command(char *cmd, t_shell *minishell)
{
	if (!cmd || !minishell)
	{
		ft_putstr_fd("Invalid command or shell context\n", STDERR_FILENO);
		minishell->last_return = 1;
		return (1);
	}
	if (ft_strcmp(cmd, "$") == 0)
	{
		minishell->last_return = minishell_error_msg(cmd, 42);
		return (1);
	}
	return (0);
}

void	load_previous_fd_to_stdin(t_shell *minishell)
{
	if (minishell->prev_fd != -1)
	{
		dup2(minishell->prev_fd, STDIN_FILENO);
		safe_close(&minishell->prev_fd);
	}
}

void	load_previous_fd_to_stdout(t_shell *minishell)
{
	if (minishell->prev_fd != -1)
	{
		dup2(minishell->prev_fd, STDOUT_FILENO);
		safe_close(&minishell->prev_fd);
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
	if (check_redirect_file(curr))
		num += 1;
	while (curr != NULL && num > 0)
	{
		curr = curr->next;
		num--;
	}
	return (curr);
}
