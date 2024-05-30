/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/05/30 20:46:48 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_exit(t_shell *minishell)
{
    // Terminate all child processes
    for (int i = 0; i < minishell->process_count; i++) {
        kill(minishell->process_ids[i], SIGTERM);  // Send termination signal
        waitpid(minishell->process_ids[i], NULL, WNOHANG);  // Clean up the zombie process
    }

    // Free resources used by the shell
    free_shell(minishell);

    // Print exit message and exit the shell
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    exit(0);
}