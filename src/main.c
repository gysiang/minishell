/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/07 09:26:15 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;
	int		p_fd[2];

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	if (pipe(p_fd) == -1)
	{
		free(shell);
		return (NULL);
	}
	shell->env_size = 0;
	shell->env = envp;
	shell->user = get_env_value(shell, "USER");
	shell->pwd = get_env_value(shell, "PWD");
	shell->home = get_env_value(shell, "HOME");
	shell->prompt = PROMPT;
	shell->cmd_list = NULL;
	shell->data_fd[0] = p_fd[0];
	shell->data_fd[1] = p_fd[1];
	shell->last_return = 0;
	shell->end = false;
	return (shell);
}

int execute_builtin(t_shell *minishell)
{
	char	*s;

	s = minishell->cmd_list->token;
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
	if (ft_strcmp(s, "echo") == 0)
	{
		//minishell_echo(minishell);
		return (1);
	}
	if (ft_strcmp(s, "env") == 0)
	{
		minishell_env(minishell);
		return (1);
	}
	if (ft_strcmp(s, "pwd") == 0)
	{
		minishell_pwd(minishell);
		return (1);
	}
	if (ft_strcmp(s, "exit") == 0)
	{
		minishell_exit();
		return (1);
	}
	return (0);
}

void	free_shell(t_shell *minishell)
{
	int	i;

	i = 0;
	if (minishell == NULL)
		return ;
	if (minishell->env != NULL)
	{
		while (minishell->env[i] != NULL)
		{
			free (minishell->env[i]);
			i++;
		}
		free(minishell->env);
	}
	if (minishell->user != NULL)
		free(minishell->user);
	if (minishell->pwd != NULL)
		free(minishell->pwd);
	if (minishell->home != NULL)
		free(minishell->home);
	if (minishell->prompt != NULL)
		free(minishell->prompt);
	free_tokenlst(minishell->cmd_list);
	free(minishell);
}


int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *line;
    t_token *token_lst;
    t_shell *g_shell;

    g_shell = init_shell(envp);
    using_history();
    setup_signal_handler();
    while (!g_shell->end)
	{
        line = readline(PROMPT);
        if (line == NULL)
		{
            printf("exit\n");
            break;
        }
        if (*line == '\0')
            continue;
        add_history(line);
        token_lst = token_processor(line, g_shell);
        //print_tokenlst(token_lst);
        if (token_lst != NULL)
            g_shell->cmd_list = token_lst;
        if (execute_builtin(g_shell) == 1)
            continue;
        pipex(g_shell);
        free_tokenlst(token_lst);
    }
    free_shell(g_shell);
    clear_history();
    return 0;
}
