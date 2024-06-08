/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/08 08:27:34 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(void)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
	{
		perror("malloc");
		return (NULL);
	}
	shell->env_size = BASE_ENV_SIZE;
	shell->prompt = PROMPT;
	shell->cmd_list = NULL;
	shell->last_return = 0;
	shell->input_fd = dup(STDIN_FILENO);
	shell->output_fd = dup(STDOUT_FILENO);
	shell->prev_fd = -1;
	shell->process_count = 0;
	shell->end = false;
	ft_memset(shell->process_ids, 0, sizeof(shell->process_ids));
	return (shell);
}

void	reset_process_ids(t_shell *minishell)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		minishell->process_ids[i] = 0;
		i++;
	}
	minishell->process_count = 0;
}

void	free_shell(t_shell *minishell)
{
	int	i;

	i = 0;
	if (minishell == NULL)
		return ;
	if (minishell->cmd_list != NULL)
		minishell->cmd_list = NULL;
	while (minishell->env[i])
	{
		free(minishell->env[i++]);
	}
	close(minishell->input_fd);
	close(minishell->output_fd);
	free(minishell->env);
	free(minishell);
}

void	initialize_shell(t_shell **minishell, char **envp)
{
	*minishell = init_shell();
	init_env(*minishell, envp);
	using_history();
	setup_signal_handler();
}

void	cleanup(t_shell *g_shell)
{
	free_shell(g_shell);
	clear_history();
}
