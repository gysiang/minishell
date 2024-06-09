/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes_utils_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:04:18 by axlee             #+#    #+#             */
/*   Updated: 2024/06/09 12:42:20 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_parse_variables(t_token *token, char **str, int *len, char **result)
{
	*str = token->token;
	*len = ft_strlen(*str) * 2; // Allocate more space to handle expansions
	*result = malloc(*len + 1);
	if (!*result)
		return ;
}

void	process_dollar_character(char *str, char *result, int *i, int *j)
{
	t_shell	*minishell;
	char	next_char;

	minishell = init_shell();
	if (str[*i + 1] == '\0')
	{
		result[(*j)++] = '$';
		(*i)++;
	}
	else
	{
		next_char = str[*i + 1];
		if (!ft_isalnum(next_char) && next_char != '_' && next_char != '?')
		{
			result[(*j)++] = '$';
			(*i)++;
		}
		else
			handle_env_variable_expansion(str, result, i, minishell);
	}
}

void	process_character(char *str, char *result, int *i, int *j)
{
	if (str[*i] == '\"')
		(*i)++;
	else if (str[*i] == '$')
		process_dollar_character(str, result, i, j);
	else
	{
		result[(*j)++] = str[*i];
		(*i)++;
	}
	result[*j] = '\0'; // Ensure null-termination
}
