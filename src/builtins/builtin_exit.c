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

static int  numeric_validation(char *cmd)
{
    int i;
    int result;
    unsigned char arg;

    i = 0;
    result = ft_atoi(cmd);
    arg =(unsigned char)result;
    if (result == 0)
    {
        while (cmd[i])
        {
            if (cmd[i] < '0' || cmd[i] > '9')
                return (-1);
            i++;
        }
    }
    return (arg);
}

#include <stdio.h>

int minishell_exit(t_shell *minishell, t_cmd *cmd)
{
    int numeric_result;

    ft_putstr_fd("exit", STDOUT_FILENO);
    numeric_result = numeric_validation(cmd->argv[1]);
    if (cmd->argv[1] && numeric_result == -1)
    {
        printf("minishell: exit: %s: numeric argument required\n", cmd->argv[1]);
        cmd->return_value = 2;
    }
    else if (cmd->argc > 2)
    {
        printf("minishell: exit: too many arguments\n");
        cmd->return_value = 1;
        return cmd->return_value;
    }
    else if (cmd->argv[1] && numeric_result != -1)
        cmd->return_value = numeric_result;
    else
        cmd->return_value = minishell->last_return;
    minishell->end = TRUE;
    return cmd->return_value;
}