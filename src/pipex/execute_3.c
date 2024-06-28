/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:45:21 by axlee             #+#    #+#             */
/*   Updated: 2024/06/28 22:59:44 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_numeric_command(t_token *curr, t_shell *minishell)
{
	if (curr->token && ft_isnumeric(curr->token))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(curr->token, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		minishell->last_return = 127;
		return (1);
	}
	return (0);
}

void	execute_single_command(t_token *curr, t_shell *minishell)
{
	int	pid;

	if (handle_numeric_command(curr, minishell))
		return ;
	pid = fork();
	if (!ft_strcmp(curr->token, "./minishell"))
		minishell->signal_received = 1;
	if (pid == 0)
	{
		signal(SIGPIPE, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		load_previous_fd_to_stdin(minishell);
		handle_redirection(minishell, curr->next);
		exec_cmd(curr, minishell);
	}
	else
	{
		if (minishell->signal_received == 1)
			signal(SIGINT, SIG_IGN);
		else
			signal(SIGINT, sigint_handler1);
		minishell->process_ids[minishell->process_count++] = pid;
		if (minishell->prev_fd != -1)
			close(minishell->prev_fd);
	}
}
