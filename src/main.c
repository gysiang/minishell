/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/15 07:30:49 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input_line(t_shell *g_shell)
{
	char	*line;
	char	*trimmed_line;

	line = NULL;
	rl_bind_key('\t', rl_insert);
	while (line == NULL)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			printf("exit\n");
			g_shell->end = 1;
			break ;
		}
		trimmed_line = line;
		while (*trimmed_line == ' ' || *trimmed_line == '\t')
			trimmed_line++;
		if (*trimmed_line == '\0')
		{
			free(line);
			line = NULL;
		}
	}
	return (line);
}

void	process_command_line(t_shell *minishell, char *line)
{
	t_token	*token_lst;
	int		saved_stdin;
	int		saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	token_lst = token_processor(line, minishell);
	print_tokenlst(token_lst);
	if (token_lst != NULL)
		minishell->cmd_list = token_lst;
	pipex(minishell);
	free_tokenlst(token_lst);
	token_lst = NULL;
	reset_minishell(minishell);
	restore_fds(saved_stdin, saved_stdout);
}


void	main_loop(t_shell *g_shell)
{
	char	*line;

	while (!g_shell->end)
	{
		line = read_input_line(g_shell);
		if (line == NULL)
		{
			g_shell->end = 1;
			break ;
		}
		add_history(line);
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
