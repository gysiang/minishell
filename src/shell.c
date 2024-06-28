/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/28 16:18:01 by gyong-si         ###   ########.fr       */
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
	shell->input_fd = -1;
	shell->output_fd = -1;
	shell->prev_fd = -1;
	shell->process_count = 0;
	shell->signal_received = 0;
	shell->end = false;
	shell->flag = 0;
	shell->redir_no = 0;
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

void	initialize_shell(t_shell **minishell, char **envp)
{
	*minishell = init_shell();
	if (*minishell == NULL)
	{
		perror("Failed to initialize shell");
		exit(1);
	}
	init_env(*minishell, envp);
	ft_using_history(*minishell);
	setup_signal_handler();
}

void	cleanup(t_shell *g_shell)
{
	rl_clear_history();
	free_shell(g_shell);
}
