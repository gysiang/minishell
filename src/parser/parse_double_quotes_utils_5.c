/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes_utils_3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:04:18 by axlee             #+#    #+#             */
/*   Updated: 2024/06/12 13:11:05 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_parse_variables(int *len, char **result)
{
	*len = *len;
	*result = *result;
}

void	initialize_parse_variables(t_token *token, t_shell *minishell)
{
	char	*str;
	int		len;
	char	*result;

	str = token->token;
	len = ft_strlen(str) * 2;
	result = malloc(len + 1);
	if (result == NULL)
		return ;
	ft_memset(result, '\0', len + 1);
	minishell->allocated_size = len + 1;
	update_parse_variables(&len, &result);
	free(result);
}

void	process_character(char *str, char **result, t_shell *minishell)
{
	if (str[minishell->i] == '\"')
		minishell->i++;
	else if (str[minishell->i] == '\'')
		(*result)[minishell->j++] = str[minishell->i++];
	else if (str[minishell->i] == '$')
		process_dollar_character(str, result, minishell);
	else if (str[minishell->i] == '\\' && str[minishell->i + 1] == '$')
	{
		(*result)[minishell->j++] = '$';
		minishell->i += 2;
	}
	else
	{
		(*result)[minishell->j] = str[minishell->i];
		minishell->j++;
		minishell->i++;
	}
	(*result)[minishell->j] = '\0';
}
