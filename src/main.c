/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/17 19:00:23 by gyong-si         ###   ########.fr       */
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

int	handle_execution(t_shell *minishell)
{
	t_token *curr;

	curr = minishell->cmd_list;
	if (check_builtin(minishell->cmd_list->token))
	{
		if (ft_strncmp(curr, "cd", 2) == 0)
			return (minishell_cd(minishell));
		if (ft_strncmp(curr, "echo", 4) == 0)
			return (minishell_echo(minishell));
		if (ft_strncmp(curr, "env", 3) == 0)
			return (minishell_env(minishell));
		if (ft_strncmp(curr, "export", 6) == 0)
			return (minishell_export(minishell));
		if (ft_strncmp(curr, "unset", 5) == 0)
			return (minishell_unset(minishell));
		if (ft_strcmp(curr, "history") == 0)
			return (print_history());
		if (ft_strcmp(curr, "history -c") == 0)
		{
			clear_history();
			return (0);
		}
	}
	else
		pipex(minishell);
	return (0);
}

/**
int execute_builtin(t_shell *minishell)
{
	char	*s;

	s = minishell->cmd_list->token;
	if (minishell->cmd_list == NULL)
        return (0);
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
} **/

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

static void handle_line(char *line, t_token *token_lst, t_shell *minishell)
{
	line = NULL;
	while (line == NULL)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			printf("exit\n");
			minishell->end = 1;
			break;
		}
		if (*line == '\0')
		{
			free(line);
			line = NULL;
		}
		if (minishell->end)
			break;
		add_history(line);
		token_lst = token_processor(line, minishell);
		print_tokenlst(token_lst);
		free(line);
		if (token_lst != NULL)
			minishell->cmd_list = token_lst;
	}
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *line;
    t_token *token_lst;
    t_shell *g_shell;

    g_shell = init_shell();
	init_env(g_shell, envp);
    using_history();
    setup_signal_handler();
    while (!g_shell->end)
    {
		handle_line(line, token_lst, g_shell);
      	handle_execution(g_shell);
        free_tokenlst(token_lst);
        token_lst = NULL;
        g_shell->cmd_list = NULL;
    }
    free_shell(g_shell);
    clear_history();
    return (0);
}
