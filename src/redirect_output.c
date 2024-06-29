/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:35:46 by axlee             #+#    #+#             */
/*   Updated: 2024/06/29 11:40:14 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_output(char *file_name, int type)
{
	int			fd;
	struct stat	buffer;

	fd = -1;
	if (access(file_name, F_OK) == 0)
	{
		if (stat(file_name, &buffer) == 0 && S_ISDIR(buffer.st_mode))
		{
			errno = EISDIR;
			return (-1);
		}
		if (access(file_name, W_OK) == -1)
		{
			errno = EACCES;
			return (-1);
		}
	}
	if (type == T_GREATER_THAN)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == T_RIGHT_SHIFT)
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

int	redirect_output(t_shell *minishell, t_token *curr)
{
	int		fd;
	int		type;
	char	*file_name;

	if (!curr || !curr->next)
		return (-1);
	file_name = curr->next->token;
	type = curr->type;
	fd = open_output(file_name, type);
	if (fd == -1)
	{
		minishell_error_msg(file_name, errno);
		minishell->last_return = 1;
		free_child_processes(minishell->cmd_list, minishell,
			minishell->last_return);
		return (-1);
	}
	else if (fd > 0)
	{
		minishell->output_fd = dup(fd);
		safe_close(&fd);
	}
	return (1);
}
