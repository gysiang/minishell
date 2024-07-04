/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:21:39 by gyong-si          #+#    #+#             */
/*   Updated: 2024/07/04 16:45:01 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_initial_command(char *s_cmd)
{
	char	*trimmed_cmd;
	char	*cmd_to_execute;

	trimmed_cmd = ft_strtrim_preserve_quotes(s_cmd, "\t");
	if (trimmed_cmd == NULL)
		return (NULL);
	if ((trimmed_cmd[0] == '"' && trimmed_cmd[ft_strlen(trimmed_cmd)
				- 1] == '"') || (trimmed_cmd[0] == '\''
			&& trimmed_cmd[ft_strlen(trimmed_cmd) - 1] == '\''))
	{
		cmd_to_execute = ft_substr(trimmed_cmd, 1, ft_strlen(trimmed_cmd) - 2);
		free(trimmed_cmd);
	}
	else
		cmd_to_execute = trimmed_cmd;
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

static char	*process_command(char *cmd, t_shell *minishell)
{
	char	*cmd_to_execute;
	char	*path;

	cmd_to_execute = process_initial_command(cmd);
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
	return (cmd_to_execute);
}

char	*get_command_path(char **s_cmd, t_shell *minishell)
{
	char		*cmd_to_execute;
	char		*path;
	struct stat	statbuf;

	cmd_to_execute = process_command(s_cmd[0], minishell);
	if (!cmd_to_execute)
		return (NULL);
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
