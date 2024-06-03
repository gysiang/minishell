/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/06/03 13:19:41 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_exit(t_shell *minishell)
{
    for (int i = 0; i < minishell->process_count; i++)
    {
        kill(minishell->process_ids[i], SIGTERM);
        waitpid(minishell->process_ids[i], NULL, WNOHANG);
    }
    free_shell(minishell);
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    exit(0);
}
