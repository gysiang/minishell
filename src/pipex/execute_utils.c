/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:21:39 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/22 16:41:41 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command(char *cmd, t_shell *minishell)
{
	if (!cmd || !minishell)
	{
		printf("Invalid command or shell context\n");
		ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
		minishell->last_return = 1;
		exit(1);
	}
	if (ft_strncmp(cmd, "$?", 2) == 0)
	{
		printf("Handling special case for last return (status\n");
		printf("%d\n", minishell->last_return);
		minishell->last_return = 0;
		exit(1);
	}
	return (0);
}

// This code resolves cat minishell.h | grep ");"$ and the pipes but will KO others. Putting it in here first
/*char	**get_command_array(char *cmd, t_shell *minishell)
{
	char	**s_cmd;
	int		arg_count;
	int		in_quotes;
	char	quote_char;
	int		arg_index;
	char	*start;

	arg_count = 0;
	in_quotes = 0;
	quote_char = 0;
	// Count arguments
	for (int i = 0; cmd[i]; i++)
	{
		if ((cmd[i] == '\'' || cmd[i] == '\"') && !in_quotes)
		{
			in_quotes = 1;
			quote_char = cmd[i];
			if (i == 0 || cmd[i - 1] == ' ')
				arg_count++;
		}
		else if (in_quotes && cmd[i] == quote_char)
		{
			in_quotes = 0;
		}
		else if (!in_quotes && cmd[i] != ' ' && (i == 0 || cmd[i - 1] == ' '))
		{
			arg_count++;
		}
	}
	s_cmd = malloc(sizeof(char *) * (arg_count + 1));
	if (!s_cmd)
	{
		ft_putstr_fd("Failed to allocate memory for command array\n",
			STDERR_FILENO);
		minishell->last_return = 1;
		return (NULL);
	}
	// Split the command
	arg_index = 0;
	in_quotes = 0;
	quote_char = 0;
	start = cmd;
	for (int i = 0; cmd[i]; i++)
	{
		if ((cmd[i] == '\'' || cmd[i] == '\"') && !in_quotes)
		{
			in_quotes = 1;
			quote_char = cmd[i];
			start = &cmd[i];
		}
		else if (in_quotes && cmd[i] == quote_char)
		{
			in_quotes = 0;
			s_cmd[arg_index++] = ft_strndup(start, &cmd[i] - start + 1);
			start = &cmd[i + 1];
		}
		else if (!in_quotes && (cmd[i] == ' ' || cmd[i + 1] == '\0'))
		{
			if (start != &cmd[i])
			{
				if (cmd[i + 1] == '\0')
					i++;
				s_cmd[arg_index++] = ft_strndup(start, &cmd[i] - start);
			}
			start = &cmd[i + 1];
		}
	}
	s_cmd[arg_index] = NULL;
	return (s_cmd);
}*/

char	**get_command_array(char *cmd, t_shell *minishell)
{
	char	**s_cmd;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
	{
		printf("Failed to split command string\n");
		ft_putstr_fd("Failed to split command\n", STDERR_FILENO);
		minishell->last_return = 1;
		exit(1);
	}
	return (s_cmd);
}

char	*get_command_path(char **s_cmd, t_shell *minishell)
{
	char		*path;
	struct stat	statbuf;

	if (s_cmd[0][0] == '/' || s_cmd[0][0] == '.')
		path = s_cmd[0];
	else
		path = get_path(s_cmd[0], minishell);
	if (!path)
	{
		minishell->last_return = minishell_error_msg(s_cmd[0], 42);
		return (NULL);
	}
	if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		minishell->last_return = minishell_error_msg(s_cmd[0], EISDIR);
		return (NULL);
	}
	return (path);
}

/*char	*get_command_path(char **s_cmd, t_shell *minishell)
{
	int		return_code;
	char	*path;
	char	**s_cmd;
	char	*path;
	int		return_code;
	int		return_code;
	char	**s_cmd;
	char	*path;
	char	**s_cmd;
	char	*path;
	int		return_code;
	int		return_code;
	int		return_code;

	return_code = 0;
	if (s_cmd[0][0] == '/' || s_cmd[0][0] == '.')
		path = s_cmd[0];
	else
		path = get_path(s_cmd[0], minishell);
	if (!path)
	{
		return_code = minishell_error_msg(s_cmd[0], 42);
		minishell->last_return (= return_code);
		return (NULL);
	}
	return (path);
}*/
static void	handle_execve_failure(char **s_cmd, t_shell *minishell,
		int error_code)
{
	int	return_code;
	
	return_code = minishell_error_msg(s_cmd[0], error_code);
	minishell->last_return = return_code;
	ft_free_tab(s_cmd);
	exit(return_code);
}

// cat-e works here
void	exec_cmd(t_token *curr, t_shell *minishell)
{
	char	**s_cmd;
	char	*path;

	// printf("Executing command: %s\n", curr->token); // Debug statement
	check_command(curr->token, minishell);
	s_cmd = get_command_array(curr->token, minishell);
	if (s_cmd[0] == NULL || ft_strlen(s_cmd[0]) == 0)
	{
		minishell->last_return = 0;
		ft_free_tab(s_cmd);
		return ;
	}
	path = get_command_path(s_cmd, minishell);
	if (!path)
	{
		ft_free_tab(s_cmd);
		return ;
	}
	if (execve(path, s_cmd, minishell->env) == -1)
	{
		// perror("execve failed"); // Debug statement
		handle_execve_failure(s_cmd, minishell, errno);
	}
	ft_free_tab(s_cmd);
}
