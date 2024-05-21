/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:09:33 by axlee             #+#    #+#             */
/*   Updated: 2024/05/21 17:27:15 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	execute_builtin_1(t_shell *minishell)
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
	if (ft_strncmp(s, "echo", 4) == 0)
	{
		printf("entered into echo\n");
		minishell_echo(minishell);
		return (1);
	}
	if (ft_strncmp(s, "env", 3) == 0)
	{
		minishell_env(minishell);
		return (1);
	}
	return (0);
}

int execute_builtin_2(t_shell *minishell)
{
    int count = 0;
    bool is_word = false;
    t_token *cmd_list = minishell->cmd_list;
    t_token *token = cmd_list;

    // Count the number of tokens
    while (token != NULL)
    {
        char *current_token = token->token;
        while (*current_token != '\0')
        {
            if (*current_token != ' ')
            {
                if (!is_word)
                {
                    count++;
                    is_word = true; // Set flag as a new word is encountered
                }
            }
            else
                is_word = false; // Set flag as the current word ends
            current_token++;
        }
        token = token->next;
    }
    token = cmd_list; // Reset token to the beginning
    if (ft_strncmp(token->token, "exit", 4) == 0)
    {
        if (count > 2) // Check if there is more than one command line (exit + argument)
        {
            minishell_error_msg("exit", 43); // Display "too many commands" error message
            return 1;
        }
        minishell_exit(minishell);
        return 1;
    }
    else if (ft_strcmp(token->token, "export") == 0)
    {
        minishell_export(minishell);
        return 1;
    }
    else if (ft_strcmp(token->token, "unset") == 0)
    {
        minishell_unset(minishell);
        return 1;
    }
    return 0;
}

/*int	execute_builtin_2(t_shell *minishell)
{
	char	*s;

	s = minishell->cmd_list->token;
	if (minishell->cmd_list == NULL)
		return (0);
	if (ft_strncmp(s, "exit", 4) == 0)
	{
		minishell_exit(minishell);
		return (1);
	}
	if (ft_strncmp(s, "export", 6) == 0)
	{
		minishell_export(minishell);
		return (1);
	}
	if (ft_strncmp(s, "unset", 5) == 0)
	{
		minishell_unset(minishell);
		return (1);
	}
	return (0);
}*/

int	other_cmds(t_shell *minishell)
{
	char	*s;

	s = minishell->cmd_list->token;
	if (minishell->cmd_list == NULL)
		return (0);
	if (ft_strcmp(s, "pwd") == 0)
	{
		minishell_pwd(minishell);
		return (1);
	}
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
	return (0);
}
