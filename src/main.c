/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/07/06 23:01:30 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_sig_received = 0;

static char	*read_multiline_input(t_shell *g_shell, char *initial_line)
{
	char	*result;
	char	*line;
	char	*temp;

	result = ft_strdup(initial_line);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			free(result);
			g_shell->end = 1;
			return (NULL);
		}
		temp = ft_strjoin(result, "\n");
		free(result);
		result = ft_strjoin(temp, line);
		free(temp);
		free(line);
		if (!check_for_unclosed_quotes(result))
			break ;
	}
	return (result);
}

char	*read_input_line(t_shell *g_shell)
{
	char	*line;
	char	*result;

	line = readline(PROMPT);
	if (line == NULL)
	{
		printf("exit\n");
		g_shell->end = 1;
		return (NULL);
	}
	if (!check_for_unclosed_quotes(line))
		return (line);
	result = read_multiline_input(g_shell, line);
	free(line);
	return (result);
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
