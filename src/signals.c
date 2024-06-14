/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:33:11 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/14 15:24:16 by gyong-si         ###   ########.fr       */
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
}

void	sigint_handler1(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	sigquit_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		(void)signal;
		rl_on_new_line();
	}
}

void	setup_signal_handler(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		ft_putstr_fd("signal", 2);
		exit(1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd("signal", 2);
		exit(1);
	}
}
