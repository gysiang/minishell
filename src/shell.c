/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/18 09:13:16 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(void)
{
	t_shell	*shell;
	int		p_fd[2];

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
	{
		perror("malloc");
		return (NULL);
	}
	if (pipe(p_fd) == -1)
	{
		free(shell);
		return (NULL);
	}
	shell->env_size = BASE_ENV_SIZE;
	shell->prompt = PROMPT;
	shell->cmd_list = NULL;
	shell->data_fd[0] = p_fd[0];
	shell->data_fd[1] = p_fd[1];
	shell->last_return = 0;
	shell->end = false;
	return (shell);
}

void	free_shell(t_shell *minishell)
{
	if (minishell == NULL)
		return ;
	if (minishell->cmd_list != NULL)
	{
		free_tokenlst(minishell->cmd_list);
		minishell->cmd_list = NULL;
	}
	free(minishell);
}
