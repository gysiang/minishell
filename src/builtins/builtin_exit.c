/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/05/30 18:16:58 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_exit(t_shell *minishell)
{
	cleanup(minishell);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(0);
}
