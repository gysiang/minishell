/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:35:43 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 11:54:29 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_error_message(int error_no)
{
	char	*error_msg;

	if (error_no == 42)
		error_msg = ft_strdup("command not found");
	else if (error_no == 43)
		error_msg = ft_strdup("too many arguments");
	else if (error_no == EISDIR)
		error_msg = ft_strdup("Is a directory");
	else if (error_no == ENOENT)
		error_msg = ft_strdup("No such file or directory");
	else if (error_no == EACCES)
		error_msg = ft_strdup("Permission denied");
	else
		error_msg = ft_strdup(strerror(error_no));
	return (error_msg);
}

static int	map_error_to_exit_code(int error_no)
{
	int	return_no;

	if (error_no == 42 || error_no == ENOENT)
		return_no = 127;
	else if (error_no == EISDIR || error_no == EACCES)
		return_no = 126;
	else
		return_no = 1; // General error
	return (return_no);
}

int	minishell_error_msg(char *cmd, int error_no)
{
	char	*error;
	char	*error_msg;
	int		return_no;

	error = ft_strdup("minishell: ");
	error = ft_strjoin_free(&error, cmd);
	error = ft_strjoin_free(&error, ": ");
	error_msg = generate_error_message(error_no);
	error = ft_strjoin_free(&error, error_msg);
	free(error_msg);
	ft_putendl_fd(error, 2);
	free(error);
	return_no = map_error_to_exit_code(error_no);
	return (return_no);
}
