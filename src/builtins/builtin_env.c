/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/04/12 12:26:46 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_env(t_shell *minishell, t_cmd *cmd)
{
	int	i;

	(void)cmd;
	i = 0;
	if (!minishell->env[i])
		return (NULL) ;
	while (minishell->env[i])
	{
		ft_putendl(minishell->env[i]);
		i++;
	}
	return (0);
}
