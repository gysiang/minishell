/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:33:11 by gyong-si          #+#    #+#             */
/*   Updated: 2024/07/07 08:33:31 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig_received = 1;
}

void	sigint_handler1(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	sigint_handler2(int signal)
{
	if (signal == SIGINT)
	{
		g_sig_received = 1;
	}
}

void	sigquit_handler(int signal)
{
	(void)signal;
}

void	setup_signal_handler(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		ft_putstr_fd("Failed to set SIGINT handler\n", STDERR_FILENO);
		exit(1);
	}
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
	{
		ft_putstr_fd("Failed to set SIGQUIT handler\n", STDERR_FILENO);
		exit(1);
	}
}
