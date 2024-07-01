/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:45:21 by axlee             #+#    #+#             */
/*   Updated: 2024/07/01 22:11:14 by gyong-si         ###   ########.fr       */
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

static void	handle_child_process(t_token *curr, t_shell *minishell)
{
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	load_previous_fd_to_stdin(minishell);
	exec_cmd(curr, minishell);
	free_child_processes(minishell->cmd_list, minishell,
		minishell->last_return);
}

static void	handle_parent_process(t_shell *minishell, int pid)
{
	if (minishell->signal_received == 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, sigint_handler1);
		signal(SIGQUIT, sigquit_handler);
	}
	minishell->process_ids[minishell->process_count++] = pid;
	if (minishell->prev_fd != -1)
		close(minishell->prev_fd);
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
		signal(SIGQUIT, SIG_DFL);
		handle_child_process(curr, minishell);
	}
	else if (pid > 0)
	{
		signal(SIGQUIT, SIG_IGN);
		handle_parent_process(minishell, pid);
	}
	else
	{
		perror("fork");
		minishell->last_return = 1;
	}
}
