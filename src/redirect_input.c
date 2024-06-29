/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 07:48:39 by axlee             #+#    #+#             */
/*   Updated: 2024/06/29 11:39:50 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input(char *file_name)
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

int	handle_input_redirection(t_shell *minishell, int type,
		char *file_name)
{
	int	fd;

	fd = -1;
	if (type == T_LESSER_THAN)
	{
		fd = open_input(file_name);
	}
	else if (type == T_LEFT_SHIFT)
	{
		fd = here_doc(minishell, file_name, 1);
	}
	if (fd == -1)
	{
		minishell->last_return = 1;
		free_child_processes(minishell->cmd_list, minishell,
			minishell->last_return);
		return (-1);
	}
	if (fd > 0)
	{
		minishell->input_fd = dup(fd);
		safe_close(&fd);
	}
	return (1);
}

int	redirect_input(t_shell *minishell, t_token *curr)
{
	int		type;
	char	*file_name;

	type = curr->type;
	file_name = curr->next->token;
	if (check_redirect_file(curr->prev))
	{
		file_name = curr->next->next->token;
	}
	return (handle_input_redirection(minishell, type, file_name));
}
