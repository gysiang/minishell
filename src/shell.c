/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/17 15:22:53 by axlee            ###   ########.fr       */
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
	shell->signal_received = 0;
	shell->end = false;
	shell->flag = 0;
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

/*void	free_shell(t_shell *minishell)
{
	int	i;
	int	i;

	if (minishell == NULL)
		return ;
	if (minishell->env)
	{
		i = 0;
		while (minishell->env[i])
		{
			free(minishell->env[i]);
			i++;
		}
		free(minishell->env);
	}
	if (minishell->cmd_list)
	{
		free_tokenlst(minishell->cmd_list);
		minishell->cmd_list = NULL;
	}
	if (minishell->input_fd != -1)
		close(minishell->input_fd);
	if (minishell->output_fd != -1)
		close(minishell->output_fd);
	free(minishell);
}*/
/*void	free_shell(t_shell *minishell)
{
	i = 0;
	if (minishell == NULL)
		return ;
	while (minishell->env[i])
	{
		free(minishell->env[i++]);
	}
	close(minishell->input_fd);
	close(minishell->output_fd);
	free(minishell->env);
	free(minishell);
}*/
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
	rl_clear_history();
}
