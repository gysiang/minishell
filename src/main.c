/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/18 09:13:16 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        if (g_shell->end)
            break;
        add_history(line);
        token_lst = token_processor(line, g_shell);
        print_tokenlst(token_lst);
        free(line);
        if (token_lst != NULL)
            g_shell->cmd_list = token_lst;
        if (execute_builtin_1(g_shell) == 1 || execute_builtin_2(g_shell) == 1 || other_cmds(g_shell) == 1)
        {
            free_tokenlst(token_lst);
            token_lst = NULL;
            g_shell->cmd_list = NULL;
            continue;
        }
        pipex(g_shell);
        free_tokenlst(token_lst);
        token_lst = NULL;
        g_shell->cmd_list = NULL;
    }
    free_shell(g_shell);
    clear_history();
    return 0;
}
