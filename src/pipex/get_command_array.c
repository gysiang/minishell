/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:52:34 by axlee             #+#    #+#             */
/*   Updated: 2024/06/23 13:52:45 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This code resolves cat minishell.h | grep ");"$ 
char	**get_command_array(char *cmd, t_shell *minishell)
{
    char	**s_cmd;
    int		arg_count;
    int		in_quotes;
    char	quote_char;
    char	*start;
    int		i;

    arg_count = 0;
    in_quotes = 0;
    quote_char = 0;
    i = 0;
    if (!cmd || *cmd == '\0')
    {
        minishell->last_return = 0;
        return (NULL);
    }
    while (cmd[i])
    {
        if ((cmd[i] == '\'' || cmd[i] == '\"') && !in_quotes)
        {
            in_quotes = 1;
            quote_char = cmd[i];
        }
        else if (in_quotes && cmd[i] == quote_char)
        {
            in_quotes = 0;
        }
        else if (!in_quotes && cmd[i] != ' ' && (i == 0 || cmd[i - 1] == ' '))
        {
            arg_count++;
        }
        i++;
    }
    s_cmd = malloc(sizeof(char *) * (arg_count + 1));
    if (!s_cmd)
    {
        minishell->last_return = 1;
        return (NULL);
    }
    arg_count = 0;
    in_quotes = 0;
    start = cmd;
    i = 0;

    while (cmd[i])
    {
        if ((cmd[i] == '\'' || cmd[i] == '\"') && !in_quotes)
        {
            in_quotes = 1;
            quote_char = cmd[i];
            start = &cmd[i + 1];
        }
        else if (in_quotes && cmd[i] == quote_char)
        {
            s_cmd[arg_count] = ft_strndup(start, &cmd[i] - start);
            arg_count++;
            in_quotes = 0;
        }
        else if (!in_quotes && (cmd[i] == ' ' || cmd[i + 1] == '\0'))
        {
            if (start != &cmd[i])
            {
                int len = &cmd[i] - start;
                if (cmd[i + 1] == '\0')
                {
                    len++;
                }
                s_cmd[arg_count] = ft_strndup(start, len);
                arg_count++;
            }
            start = &cmd[i + 1];
        }
        i++;
    }
    s_cmd[arg_count] = NULL;
    return (s_cmd);
}
