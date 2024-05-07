/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:33:11 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/07 10:10:44 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int signal)
{
    if (signal == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void sigquit_handler(int signal)
{
    if (signal == SIGQUIT)
    {
        (void)signal;
        rl_on_new_line();
        rl_redisplay();
    }
}

void setup_signal_handler(void)
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
