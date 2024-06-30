/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:11:44 by axlee             #+#    #+#             */
/*   Updated: 2024/06/30 20:12:08 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_expr_exit_status_token(t_token *curr, t_shell *minishell)
{
	char	*expanded_expr;
	char	*exit_status_str;

	expanded_expr = ft_strdup("expr ");
	exit_status_str = ft_itoa(minishell->last_return);
	expanded_expr = ft_strjoin_free(&expanded_expr, exit_status_str);
	expanded_expr = ft_strjoin_free(&expanded_expr, " + ");
	expanded_expr = ft_strjoin_free(&expanded_expr, exit_status_str);
	free(curr->token);
	curr->token = expanded_expr;
	free(exit_status_str);
}
