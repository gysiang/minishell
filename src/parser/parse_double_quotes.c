/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:00:03 by axlee             #+#    #+#             */
/*   Updated: 2024/06/15 09:58:20 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_double_quotes(t_token *token, t_shell *minishell)
{
	char	*str;
	char	*result;

	minishell->i = 0;
	minishell->j = 0;
	initialize_parse_variables(token, minishell);
	str = token->token;
	result = malloc(minishell->allocated_size);
	if (result == NULL)
		return ;
	result[0] = '\0';
	if (str[minishell->i] == '\0')
	{
		free(token->token);
		result = "";
	}
	else
	{
		while (str[minishell->i] != '\0')
			process_character(str, &result, minishell);
		free(token->token);
	}
	token->token = ft_strdup(result);
	free(result);
}
