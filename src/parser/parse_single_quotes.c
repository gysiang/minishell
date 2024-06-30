/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:49:34 by axlee             #+#    #+#             */
/*   Updated: 2024/06/30 20:25:26 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_single_quotes(t_token *token)
{
	char	*str;
	char	*new_str;
	int		len;

	str = token->token;
	len = ft_strlen(str);
	if (len > 1 && str[0] == '\'' && str[len - 1] == '\'')
	{
		new_str = ft_strndup(str + 1, len - 2);
		if (new_str)
		{
			free(token->token);
			token->token = new_str;
		}
	}
}
