/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/18 08:48:08 by gyong-si         ###   ########.fr       */
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
	shell->end = false;
	return (shell);
}

int	check_builtin(char *s)
{
	if (!ft_strncmp(s, "cd", 2) || !ft_strcmp(s, "echo")
		|| !ft_strncmp(s, "env", 3) || !ft_strcmp(s, "pwd")
		|| !ft_strncmp(s, "export", 6) || !ft_strncmp(s, "unset", 5)
		|| !ft_strcmp(s, "history") || !ft_strcmp(s, "history -c"))
	{
		return (1);
	}
	return (0);
}

int execute_builtin(t_shell *minishell)
{
	char	*s;

	s = minishell->cmd_list->token;
	if (minishell->cmd_list == NULL)
		return (0);
	if (ft_strcmp(s, "history") == 0)
	{
		print_history();
		return (1);
	}
	if (ft_strcmp(s, "history -c") == 0)
	{
		clear_history();
		return (1);
	}
	if (ft_strncmp(s, "cd", 2) == 0)
	{
		minishell_cd(minishell);
		return (1);
    }
	if (ft_strcmp(s, "echo") == 0)
	{
		minishell_echo(minishell);
		return (1);
	}
	if (ft_strncmp(s, "env", 3) == 0)
	{
		minishell_env(minishell);
		return (1);
	}
	if (ft_strcmp(s, "pwd") == 0)
	{
		minishell_pwd(minishell);
		return (1);
	}
	if (ft_strncmp(s, "exit", 4) == 0)
	{
		minishell_exit(minishell);
		return (1);
	}
	if (ft_strncmp(s, "export", 6) == 0)
	{
		printf("calling export\n");
		minishell_export(minishell);
		return (1);
	}
	if (ft_strncmp(s, "unset", 5) == 0)
	{
		printf("calling unset\n");
		minishell_unset(minishell);
		return (1);
	}
	return (0);
}

void free_shell(t_shell *minishell)
{
	if (minishell == NULL)
		return;
	if (minishell->cmd_list != NULL)
	{
		free_tokenlst(minishell->cmd_list);
		minishell->cmd_list = NULL;
	}
	free(minishell);
}

char	*read_input_line(t_shell *g_shell)
{
	char *line;

	line = NULL;
	while (line == NULL)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			printf("exit\n");
			g_shell->end = 1;
			break;
		}
		if (*line == '\0')
		{
			free(line);
			line = NULL;
		}
	}
	return (line);
}

void	initialize_shell(t_shell **minishell, char **envp)
{
	*minishell = init_shell();
	init_env(*minishell, envp);
	using_history();
	setup_signal_handler();
}

void	process_command_line(t_shell *minishell, char *line)
{
	t_token *token_lst;

	token_lst = token_processor(line, minishell);
	print_tokenlst(token_lst);
	if (token_lst != NULL)
		minishell->cmd_list = token_lst;
	if (execute_builtin(minishell) != 1)
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

void	cleanup(t_shell *g_shell)
{
	free_shell(g_shell);
	clear_history();
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
