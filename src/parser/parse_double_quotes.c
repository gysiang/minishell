/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:00:03 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 00:42:05 by gyong-si         ###   ########.fr       */
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
	while (str[indices.i] != '\0')
	{
		process_character(str, result, minishell, &indices);
	}
	token->token = ft_strdup(result);
	token->is_single_quoted = 0;
}
