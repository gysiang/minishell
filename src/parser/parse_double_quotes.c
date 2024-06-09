/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:00:03 by axlee             #+#    #+#             */
/*   Updated: 2024/06/09 12:58:20 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_double_quotes(t_token *token)
{
	char	*str;
	int		len;
	char	*result;
	int		i;
	int		j;

	initialize_parse_variables(token, &str, &len, &result);
	if (!result)
		return ;
    i = 0;
    j = 0;
	while (i < len)
		process_character(str, result, &i, &j);
	result[j] = '\0';
	free(token->token);
	token->token = result;
	token->is_single_quoted = 0;
}
