/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/05/12 00:23:36 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_env(t_shell *minishell)
{
    int i;

    i = 0;
    if (!minishell->env || !minishell->env[0])
        return;
    while (minishell->env[i])
    {
        ft_putendl_fd(minishell->env[i], 1);
        i++;
    }
}
