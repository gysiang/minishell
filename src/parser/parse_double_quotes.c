/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:00:03 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 00:58:57 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_double_quotes(t_token *token, t_shell *minishell)
{
	char	*str;
	int		len;
	char	*result;

	minishell->i = 0;
	minishell->j = 0;
	initialize_parse_variables(token, &str, &len, &result);
	if (!result)
		return ;
	while (str[minishell->i] != '\0')
	{
		process_character(str, result, minishell);
	}
	token->token = ft_strdup(result);
	token->is_single_quoted = 0;
}
