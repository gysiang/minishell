/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:33:11 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/12 15:59:59 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		fflush(stdout);
		prompt();
		printf(" ");
	}
}

void	sigquit_handler(int signal)
{
	(void)signal;
}

void	setup_signal_handler()
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		ft_putstr_fd("signal", 2);
		exit(1);
	}
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
	{
		ft_putstr_fd("signal", 2);
		exit(1);
	}
}
