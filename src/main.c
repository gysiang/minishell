/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/20 14:01:01 by gyong-si         ###   ########.fr       */
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
			break;
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
	t_token *token_lst;

	token_lst = token_processor(line, minishell);
	print_tokenlst(token_lst);
	if (token_lst != NULL)
		minishell->cmd_list = token_lst;
	if (execute_builtin_1(minishell) != 1 || execute_builtin_2(minishell) != 1 || other_cmds(minishell) != 1)
		pipex(minishell);
	free_tokenlst(token_lst);
	token_lst = NULL;
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
	(void)argc;
	(void)argv;
	t_shell *g_shell;

	initialize_shell(&g_shell, envp);
	main_loop(g_shell);
	cleanup(g_shell);
	return (0);
}
