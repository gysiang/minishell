/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:06:17 by axlee             #+#    #+#             */
/*   Updated: 2024/06/02 21:56:09 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_env(t_shell *minishell)
{
	int	i;

	printf("Entering minishell_env function\n"); // Debug print

	i = 0;
	if (!minishell->env || !minishell->env[0])
	{
		printf("No environment variables to print\n"); // Debug print
		return (0);
	}
	env_len(minishell);
	while (minishell->env[i])
	{
		printf("env %d : ", i);
		printf("%s\n", minishell->env[i]);
		i++;
	}

	printf("Exiting minishell_env function\n"); // Debug print
	return (0);
}

/*int	minishell_env(t_shell *minishell)
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
}*/
