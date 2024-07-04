/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_array_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:52:34 by axlee             #+#    #+#             */
/*   Updated: 2024/07/04 18:27:24 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote_cmd(char **cmd, char **start, int *in_quotes,
		char *quote_char)
{
	*in_quotes = 1;
	*quote_char = **cmd;
	*start = *cmd + 1;
	(*cmd)++;
}

void	handle_closing_quote(char **cmd, char **start, char **s_cmd,
		int *arg_count)
{
	s_cmd[(*arg_count)++] = ft_strndup(*start, *cmd - *start);
	*start = *cmd + 1;
	(*cmd)++;
}

void	handle_space(char **cmd, char **start, char **s_cmd, int *arg_count)
{
	if (*cmd != *start)
	{
		s_cmd[(*arg_count)++] = ft_strndup(*start, *cmd - *start);
		*start = *cmd + 1;
	}
	(*cmd)++;
}

void	handle_last_argument(char **cmd, char **start, int *is_last_arg,
		int *arg_count)
{
	if (!*is_last_arg && (*arg_count > 0) && (ft_strchr(*cmd, ';')
			|| ft_strchr(*cmd, '$')))
	{
		*is_last_arg = 1;
		*start = *cmd;
	}
	(*cmd)++;
}

void	finalize_command_array(char *start, char *cmd, char **s_cmd,
		int *arg_count)
{
	if (start < cmd)
		s_cmd[(*arg_count)++] = ft_strndup(start, cmd - start);
	s_cmd[*arg_count] = NULL;
}
