/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:00:03 by axlee             #+#    #+#             */
/*   Updated: 2024/06/09 22:27:47 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_double_quotes(t_token *token, t_shell *minishell)
{
	char		*str;
	int			len;
	char		*result;
	t_indices	indices;

	indices.i = 0;
	indices.j = 0;
	initialize_parse_variables(token, &str, &len, &result);
	if (!result)
		return ;
	while (str[indices.i] != '\0')
	{
		process_character(str, result, minishell, &indices);
	}
	result[indices.j] = '\0';
	free(token->token);
	token->token = result;
	token->is_single_quoted = 0;
}
