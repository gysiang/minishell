/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:21:39 by gyong-si          #+#    #+#             */
/*   Updated: 2024/07/04 13:41:44 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quotes_for_trim(const char *str, int *in_quotes,
		char *quote_char, int i)
{
	if ((str[i] == '"' || str[i] == '\'') && !(*in_quotes))
	{
		*in_quotes = 1;
		*quote_char = str[i];
	}
	else if (str[i] == *quote_char && *in_quotes)
		*in_quotes = 0;
}

char	*ft_strtrim_preserve_quotes(char *str, char *set)
{
	int		start;
	int		end;
	int		in_quotes;
	char	quote_char;
	int		i;

	start = 0;
	end = ft_strlen(str) - 1;
	in_quotes = 0;
	quote_char = 0;
	while (str[start] && ft_strchr(set, str[start]))
		start++;
	while (end > start && ft_strchr(set, str[end]))
		end--;
	i = start;
	while (i <= end)
	{
		handle_quotes_for_trim(str, &in_quotes, &quote_char, i);
		i++;
	}
	return (ft_substr(str, start, end - start + 1));
}

static char	*process_initial_command(char *s_cmd)
{
	char	*trimmed_cmd;
	char	*cmd_to_execute;

	trimmed_cmd = ft_strtrim_preserve_quotes(s_cmd, " \t");
	if (trimmed_cmd == NULL)
		return (NULL);
	cmd_to_execute = ft_strtrim(trimmed_cmd, "\"'");
	free(trimmed_cmd);
	return (cmd_to_execute);
}

static char	*get_path_by_command_type(char *cmd, t_shell *minishell)
{
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	else if (cmd[0] == '$')
		return (get_env_value(minishell, cmd + 1, 1));
	else
		return (get_path(cmd, minishell));
}

char	*get_command_path(char **s_cmd, t_shell *minishell)
{
	char		*path;
	struct stat	statbuf;
	char		*cmd_to_execute;

	cmd_to_execute = process_initial_command(s_cmd[0]);
	if (cmd_to_execute == NULL || *cmd_to_execute == '\0')
	{
		free(cmd_to_execute);
		return (NULL);
	}
	if (cmd_to_execute[0] == '$')
	{
		path = get_env_value(minishell, cmd_to_execute + 1, 1);
		free(cmd_to_execute);
		return (path);
	}
	path = get_path_by_command_type(cmd_to_execute, minishell);
	if (!path)
	{
		free(cmd_to_execute);
		return (NULL);
	}
	if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		minishell->last_return = minishell_error_msg(cmd_to_execute, EISDIR);
		free(path);
		free(cmd_to_execute);
		return (NULL);
	}
	free(cmd_to_execute);
	return (path);
}
