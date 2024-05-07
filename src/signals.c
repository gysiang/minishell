/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:33:11 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/06 20:08:39 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int signal)
{
	if (signal == SIGINT)
    {
        printf("\n");
        prompt();
        printf(" ");
    }
}

void sigquit_handler(int signal)
{
    if (signal == SIGQUIT)
    {
        // Handle the SIGQUIT signal (e.g., cleanup, exit the program)
        exit(0);
    }
}

void setup_signal_handler(void)
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
