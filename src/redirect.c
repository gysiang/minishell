/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 07:48:39 by axlee             #+#    #+#             */
/*   Updated: 2024/06/27 09:59:01 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_input(char *file_name)
{
	int			fd;
	struct stat	buffer;

	if (stat(file_name, &buffer) == -1)
	{
		minishell_error_msg(file_name, ENOENT);
		return (-1);
	}
	if (S_ISDIR(buffer.st_mode))
	{
		minishell_error_msg(file_name, EISDIR);
		return (-1);
	}
	if (access(file_name, R_OK) == -1)
	{
		minishell_error_msg(file_name, EACCES);
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

/*static int	open_input(char *file_name)
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
}*/
int	check_redirect_file(t_token *curr)
{
	if (!ft_strcmp(curr->token, "cat") && curr->next && curr->next->next
		&& curr->next->next->next && check_redirection_type(curr->next)
		&& curr->next->next->type == T_FILE
		&& curr->next->next->next->type == T_IDENTIFIER
		&& !curr->next->next->next->next)
	{
		return (1);
	}
	return (0);
}

int	redirect_input(t_shell *minishell, t_token *curr)
{
	int		fd;
	int		type;
	char	*file_name;

	fd = -1;
	type = curr->type;
	file_name = curr->next->token;
	if (check_redirect_file(curr->prev))
		file_name = curr->next->next->token;
	if (type == T_LESSER_THAN)
		fd = open_input(file_name);
	else if (type == T_LEFT_SHIFT)
		fd = here_doc(minishell, file_name, 1);
	if (fd == -1)
	{
		minishell->last_return = 1;
		exit(1);
		return (-1);
	}
	if (fd > 0)
	{
		minishell->input_fd = dup(fd);
		safe_close(&fd);
	}
	return (1);
}

/*int	redirect_input(t_shell *minishell, t_token *curr)
{
	int			fd;
	int			type;
	char		*file_name;
	struct stat	buffer;
	int			fd;
	int			fd;
	struct stat	buffer;

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
}*/
// Edit
static int	open_output(char *file_name, int type)
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

/*static int	open_output(char *file_name, int type)
{
	int			fd;
	struct stat	buffer;
	int			fd;
	int			type;
	char		*file_name;

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
			minishell_error_msg(file_name, EACCES);
			return (-1);
		}
	}
	if (type == T_GREATER_THAN)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == T_RIGHT_SHIFT)
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		perror("open");echo
	return (fd);
}*/
int	redirect_output(t_shell *minishell, t_token *curr)
{
	int			fd;
	int			type;
	char		*file_name;

	if (!curr || !curr->next)
		return (-1);
	file_name = curr->next->token;
	type = curr->type;
	fd = open_output(file_name, type);
	if (fd == -1)
	{
		minishell->last_return = minishell_error_msg(file_name, errno);
		exit(1);
		return (-1);
	}
	else if (fd > 0)
	{
		minishell->output_fd = dup(fd);
		safe_close(&fd);
	}
	return (1);
}
