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

void minishell_exit(void)
{
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    // Any cleanup or additional actions before exiting can be done here
    exit(0);
}
/*int minishell_exit(t_shell *minishell)
{
    ft_putstr_fd("exit", STDOUT_FILENO);

    // Check if there are too many arguments
    if (minishell->cmd_list != NULL && minishell->cmd_list->argc > 1)
    {
        printf("minishell: exit: too many arguments\n");
        return 1;
    }

    minishell->end = true;
    return 0;
}*/