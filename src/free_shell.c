/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:22:18 by axlee             #+#    #+#             */
/*   Updated: 2024/06/17 15:30:21 by axlee            ###   ########.fr       */
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
	if (minishell->cmd_list)
	{
		free_tokenlst(minishell->cmd_list);
		minishell->cmd_list = NULL;
	}
	if (minishell->input_fd != -1)
		close(minishell->input_fd);
	if (minishell->output_fd != -1)
		close(minishell->output_fd);
	if (minishell->prompt && ft_strcmp(minishell->prompt, PROMPT) != 0)
		free(minishell->prompt);
	free(minishell);
}
