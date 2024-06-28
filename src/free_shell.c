/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:22:18 by axlee             #+#    #+#             */
/*   Updated: 2024/06/28 16:37:00 by gyong-si         ###   ########.fr       */
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
	free(minishell);
}

void	free_child_processes(t_token *curr, t_shell *minishell, int exit_code)
{
	if (curr != NULL)
		free_tokenlst(curr);
	curr = NULL;
	safe_close(&minishell->saved_stdin);
	safe_close(&minishell->saved_stdout);
	free_shell(minishell);
	exit(exit_code);
}
