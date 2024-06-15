/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 07:48:39 by axlee             #+#    #+#             */
/*   Updated: 2024/06/15 13:04:43 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_input(char *file_name)
{
	int			fd;
	struct stat	buffer;

	if (stat(file_name, &buffer) == -1 || S_ISDIR(buffer.st_mode))
	{
		minishell_error_msg(file_name, 2);
		return (-1);
	}
	if (access(file_name, R_OK) == -1)
	{
		minishell_error_msg(file_name, 3);
		return (-1);
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (fd);
	}
	return (fd);
}

int	redirect_input(t_shell *minishell, t_token *curr)
{
	int		fd;
	int		type;
	char	*file_name;

	fd = -1;
	type = curr->type;
	file_name = curr->next->token;
	if (type == T_LESSER_THAN)
		fd = open_input(file_name);
	else if (type == T_LEFT_SHIFT)
	{
		fd = here_doc(minishell, file_name, 1);
	}
	return (fd);
}

static int	open_output(char *file_name, int type)
{
	struct stat	buffer;
	int			fd;

	fd = -1;
	if (access(file_name, F_OK) == 0)
	{
		if (stat(file_name, &buffer) == 0 && S_ISDIR(buffer.st_mode))
		{
			minishell_error_msg(file_name, 2);
			return (-1);
		}
		if (access(file_name, W_OK) == -1)
		{
			minishell_error_msg(file_name, 3);
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
	if (fd > 0)
		minishell->output_fd = fd;
	return (fd);
}
