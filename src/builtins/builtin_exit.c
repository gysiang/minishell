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

int	minishell_exit(t_shell *minishell, t_cmd *cmd)
{
    int numeric_result;

    ft_putstr_fd("exit", STDOUT_FILENO);
    numeric_result = numeric_validation(cmd->argv[1]);
    if (cmd->argv[1] && numeric_result == -1)
    {
        ft_putstr_fd("minishell: exit: %s: numeric arguement required\n", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
        ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
        cmd->return_value = 2;
    }
    else if (cmd->argc > 2)
    {
        ft_prinf("minishell: exit: too many arguements\n");
        cmd->return_value = 1;
        return (cmd->return_value);
    }
    else if (cmd->argv[1] && numeric_result != -1)
        cmd->return_value = numeric_result;
    else
        cmd->return_value = minishell->last_return;
    minishell->end = TRUE;
    return (cmd->return_value);
}