/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/07/06 00:36:48 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig_received = 0;

char	*read_input_line(t_shell *g_shell)
{
	char	*line;
	char	*trimmed_line;

	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			printf("exit\n");
			g_shell->end = 1;
			return (NULL);
		}
		trimmed_line = line;
		while (*trimmed_line == ' ' || *trimmed_line == '\t')
			trimmed_line++;
		if (*trimmed_line != '\0')
			return (line);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		free(line);
	}
}

void	process_command_line(t_shell *minishell, char *line)
{
	t_token	*token_lst;

	if (hist_feature(line, minishell))
	{
		return ;
	}
	minishell->saved_stdin = dup(STDIN_FILENO);
	minishell->saved_stdout = dup(STDOUT_FILENO);
	token_lst = token_processor(line, minishell);
	//print_tokenlst(token_lst);
	if (token_lst != NULL)
		minishell->cmd_list = token_lst;
	if (line && ft_strlen(line) > 0)
		pipex(minishell);
	free_tokenlst(token_lst);
	token_lst = NULL;
	reset_minishell(minishell);
	restore_fds(&minishell->saved_stdin, &minishell->saved_stdout);
}

void	main_loop(t_shell *g_shell)
{
	char	*line;

	while (!g_shell->end)
	{
		signal(SIGQUIT, SIG_IGN);
		line = read_input_line(g_shell);
		if (line == NULL)
		{
			g_shell->end = 1;
			break ;
		}
		add_to_history(g_shell, line);
		if (g_sig_received == 1)
		{
			g_shell->last_return = 130;
			g_sig_received = 0;
		}
		process_command_line(g_shell, line);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*g_shell;

	(void)argc;
	(void)argv;
	initialize_shell(&g_shell, envp);
	main_loop(g_shell);
	cleanup(g_shell);
	return (0);
}
