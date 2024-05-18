/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/05/17 23:33:12 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_env(t_shell *minishell)
{
	int	i;

	i = 0;
	if (!minishell->env || !minishell->env[0])
		return (0);
	env_len(minishell);
	while (minishell->env[i])
	{
		printf("env %d : ", i);
		printf("%s\n", minishell->env[i]);
		i++;
	}
	return (0);
}
