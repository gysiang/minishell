/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:54:29 by axlee             #+#    #+#             */
/*   Updated: 2024/07/06 00:16:56 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expr_exit_status(const char *str)
{
	return (ft_strncmp(str, "expr $? + $?", 12) == 0);
}

void	handle_expr_exit_status(char **line, t_token **token_lst)
{
	char	*token;

	token = ft_strdup("expr $? + $?");
	token_add_back(token_lst, token, T_IDENTIFIER, 0);
	*line += 12;
}
