/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:22:18 by axlee             #+#    #+#             */
/*   Updated: 2024/06/27 12:26:29 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
}

void	free_shell(t_shell *minishell)
{
	if (minishell == NULL)
		return ;
	free_env(minishell->env);
	ft_free_history(minishell);
	safe_close(&minishell->input_fd);
	safe_close(&minishell->output_fd);
	safe_close(&minishell->prev_fd);
	safe_close(&minishell->saved_stdin);
	safe_close(&minishell->saved_stdout);
	if (minishell->prompt && ft_strcmp(minishell->prompt, PROMPT) != 0)
		free(minishell->prompt);
	free(minishell);
}
