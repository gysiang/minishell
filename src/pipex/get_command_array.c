/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:52:34 by axlee             #+#    #+#             */
/*   Updated: 2024/07/04 13:39:54 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This code resolves cat minishell.h | grep ");"$
static char	**initialize_command_array(char *cmd, t_shell *minishell)
{
	char	**s_cmd;

	// printf("Debug: Initial command: %s\n", cmd);
	if (!cmd || *cmd == '\0')
	{
		minishell->last_return = 0;
		return (NULL);
	}
	s_cmd = malloc(sizeof(char *) * (ft_strlen(cmd) + 1));
	if (!s_cmd)
	{
		minishell->last_return = 1;
		return (NULL);
	}
	return (s_cmd);
}

static void	handle_quote_cmd(char **cmd, char **start, int *in_quotes,
		char *quote_char)
{
	*in_quotes = 1;
	*quote_char = **cmd;
	*start = *cmd + 1;
	(*cmd)++;
}

/*static void	handle_non_quote_cmd(char **cmd, char **start, char **s_cmd,
		int *arg_count)
{
	int		len;
	int		is_last;
	int		in_quotes;
	char	quote_char;
	char	*start;
	int		is_last_arg;

	is_last = (*(*cmd + 1) == '\0');
	len = *cmd - *start + is_last;
	if (*start != *cmd)
	{
		s_cmd[*arg_count] = ft_strndup(*start, len);
		(*arg_count)++;
	}
	else
	{
		s_cmd[*arg_count] = ft_strndup(*start, 1);
		(*arg_count)++;
	}
	*start = *cmd + 1;
	(*cmd)++;
}*/
static void	parse_command(char *cmd, char **s_cmd, int *arg_count)
{
	int		in_quotes;
	char	quote_char;
	char	*start;
	int		is_last_arg;

	in_quotes = 0;
	quote_char = 0;
	start = cmd;
	is_last_arg = 0;
	while (*cmd)
	{
		if ((*cmd == '\'' || *cmd == '\"') && !in_quotes)
			handle_quote_cmd(&cmd, &start, &in_quotes, &quote_char);
		else if (in_quotes && *cmd == quote_char)
		{
			s_cmd[(*arg_count)++] = ft_strndup(start, cmd - start);
			in_quotes = 0;
			cmd++;
		}
		else if (!in_quotes && *cmd == ' ' && !is_last_arg)
		{
			if (cmd != start)
			{
				s_cmd[(*arg_count)++] = ft_strndup(start, cmd - start);
				start = cmd + 1;
			}
			cmd++;
		}
		else
		{
			if (!is_last_arg && (*arg_count > 0) && (ft_strchr(cmd, ';')
					|| ft_strchr(cmd, '$')))
			{
				is_last_arg = 1;
				start = cmd;
			}
			cmd++;
		}
	}
	if (start < cmd)
		s_cmd[(*arg_count)++] = ft_strndup(start, cmd - start);
	s_cmd[*arg_count] = NULL;
}

char	**get_command_array(char *cmd, t_shell *minishell)
{
	char	**s_cmd;
	int		arg_count;

	arg_count = 0;
	s_cmd = initialize_command_array(cmd, minishell);
	if (!s_cmd)
		return (NULL);
	parse_command(cmd, s_cmd, &arg_count);
	// printf("Debug: Final command array:\n");
	// for (int i = 0; s_cmd[i] != NULL; i++)
	// printf("  [%d]: %s\n", i, s_cmd[i]);
	return (s_cmd);
}
