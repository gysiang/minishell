/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:47:49 by axlee             #+#    #+#             */
/*   Updated: 2024/07/06 12:49:25 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	sigpipe_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("Broken pipe", 2);
	exit(1);
}
