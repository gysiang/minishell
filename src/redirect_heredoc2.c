/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:17:59 by gyong-si          #+#    #+#             */
/*   Updated: 2024/07/05 00:44:11 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_exit(int signal_number)
{
	if (signal_number == SIGINT)
	{
		g_sig_received = 1;
		exit(130);
	}
}

void	error_eof(char *end_of_file, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: warning: here_document delimited by ", 2);
		ft_putstr_fd("end-of-file (wanted ", 2);
		ft_putstr_fd(end_of_file, 2);
		ft_putendl_fd(")", 2);
	}
	if (i == 2)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking ", 2);
		ft_putstr_fd("for matching '", 2);
		ft_putstr_fd(end_of_file, 2);
		ft_putstr_fd("'\n", 2);
		ft_putstr_fd("minishell: syntax error: unexpected end of file", 2);
	}
}
