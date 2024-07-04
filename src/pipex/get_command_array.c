/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:52:34 by axlee             #+#    #+#             */
/*   Updated: 2024/07/04 18:28:23 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**initialize_command_array(char *cmd, t_shell *minishell)
{
	char	**s_cmd;

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
			handle_closing_quote(&cmd, &start, s_cmd, arg_count);
			in_quotes = 0;
		}
		else if (!in_quotes && *cmd == ' ' && !is_last_arg)
			handle_space(&cmd, &start, s_cmd, arg_count);
		else
			handle_last_argument(&cmd, &start, &is_last_arg, arg_count);
	}
	finalize_command_array(start, cmd, s_cmd, arg_count);
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
	return (s_cmd);
}
