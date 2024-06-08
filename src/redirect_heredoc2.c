/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:17:59 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/08 22:18:53 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_exit(int signal_number)
{
	(void)signal_number;
	exit(0);
}

void	error_eof(char *end_of_file)
{
	ft_putstr_fd("minishell: warning: here_document delimited by", 2);
	ft_putstr_fd("end-of-file (wanted ", 2);
	ft_putstr_fd(end_of_file, 2);
	ft_putendl_fd(")", 2);
}
