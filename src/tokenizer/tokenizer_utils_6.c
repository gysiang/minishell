/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:54:29 by axlee             #+#    #+#             */
/*   Updated: 2024/06/29 19:54:39 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// SPECIAL
int	is_expr_exit_status(const char *str)
{
	return (strncmp(str, "expr $? + $?", 12) == 0);
}

// SPECIAL
void	handle_expr_exit_status(char **line, t_token **token_lst)
{
	char	*token;

	token = ft_strdup("expr $? + $?");
	token_add_back(token_lst, token, T_IDENTIFIER);
	*line += 12;
}