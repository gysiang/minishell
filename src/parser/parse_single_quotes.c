/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:49:34 by axlee             #+#    #+#             */
/*   Updated: 2024/06/11 11:35:06 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	*remove_single_quotes(const char *str)
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
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && str[i + 1] == '\'')
			i += 2;
		else
			result[j++] = str[i++];
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
}*/

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
