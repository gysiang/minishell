/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/05/17 11:32:49 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_env(t_shell *minishell)
{
	int	i;

	i = 0;
	if (!minishell->env || !minishell->env[0])
		return ;
	env_len(minishell);
	while (minishell->env[i])
	{
		printf("env %d : ", i);
		printf("%s\n", minishell->env[i]);
		i++;
	}
}
