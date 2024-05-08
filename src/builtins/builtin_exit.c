/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/04/12 12:26:46 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_exit(t_shell *minishell)
{
    free_shell(minishell);
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    exit(0);
}

/*void minishell_exit(void)
{
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    // Any cleanup or additional actions before exiting can be done here
    exit(0);
}*/