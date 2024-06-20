/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/06/20 14:19:36 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	minishell_env(t_shell *minishell)
{
	int	i;

	printf("Entering minishell_env function\n");
	i = 0;
	if (!minishell->env || !minishell->env[0])
	{
		printf("No environment variables to print\n");
		return (0);
	}
	sort_env(minishell);
	env_len(minishell);
	while (minishell->env[i])
	{
		printf("env %d : ", i);
		printf("%s\n", minishell->env[i]);
		i++;
	}
	printf("Exiting minishell_env function\n");
	return (0);
}*/

int	minishell_env(t_shell *minishell)
{
	int	i;

	i = 0;
	if (!minishell->env || !minishell->env[0])
	{
		printf("No environment variables to print\n");
		return (0);
	}
	sort_env(minishell);
	while (minishell->env[i])
	{
		printf("%s\n", minishell->env[i]);
		i++;
	}
	return (0);
}
