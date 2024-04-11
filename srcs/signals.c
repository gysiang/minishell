/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:33:11 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/11 21:19:30 by gyong-si         ###   ########.fr       */
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
		put_string_fd(2, "signal");
		exit(1);
	}
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
	{
		put_string_fd(2, "signal");
		exit(1);
	}
}
