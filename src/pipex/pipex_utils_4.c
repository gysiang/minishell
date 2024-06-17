/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:23:30 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/17 17:05:34 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_handler(int exit_code)
{
	if (exit_code == 1)
		ft_putstr_fd("infile cmd cmd outfile\n", 2);
	exit(EXIT_FAILURE);
}

int	open_file(const char *file, int mode)
{
	int	return_fd;

	if (mode == 0)
		return_fd = open(file, O_RDONLY, 0777);
	else
		return_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (return_fd == -1)
		exit_handler(1);
	return (return_fd);
}

void	restore_fds(int input_fd, int output_fd)
{
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
}
