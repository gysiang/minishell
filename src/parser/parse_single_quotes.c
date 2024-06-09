/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:49:34 by axlee             #+#    #+#             */
/*   Updated: 2024/06/09 18:39:22 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_single_quotes(const char *str)
{
	int		len;
	char	*result;
	int		i;
	int		j;

	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	parse_single_quotes(t_token *token)
{
	char	*result;

	if ((ft_strlen(token->token) == 2 && token->token[0] == '\''
			&& token->token[1] == '\'') || (ft_strlen(token->token) == 2
			&& token->token[0] == '\"' && token->token[1] == '\"'))
		result = ft_strdup("");
	else
		result = remove_single_quotes(token->token);
	if (!result)
		return ;
	free(token->token);
	token->token = result;
	token->is_single_quoted = 1;
}
