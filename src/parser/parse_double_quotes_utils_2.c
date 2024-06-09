/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes_utils_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:04:18 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 00:59:26 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_parse_variables(t_token *token, char **str, int *len,
		char **result)
{
	*str = token->token;
	*len = ft_strlen(*str) * 2;
	*result = malloc(*len + 1);
	if (!*result)
		return ;
	(*result)[0] = '\0';
}

void	process_special_dollar_cases(char *str, char *result,
		t_shell *minishell)
{
	char	next_char;
	char	exit_status[12];
	int		length;

	next_char = str[indices->i + 1];
	if (next_char == '?')
	{
		length = snprintf(exit_status, sizeof(exit_status), "%d",
				minishell->last_return);
		if (length > 0)
		{
			strcpy(&result[minishell->j], exit_status);
			minishell->j += strlen(exit_status);
		}
		minishell->i += 2;
	}
	else if (!ft_isalnum(next_char) && next_char != '_' && next_char != '\"')
	{
		result[minishell->j++] = '$';
		result[minishell->j++] = next_char;
		minishell->i += 2;
	}
	else if (next_char == '\"')
	{
		result[minishell->j++] = '$';
		minishell->i++;
	}
	else
	{
		handle_env_variable_expansion(str, result, minishell);
	}
}

void	process_dollar_character(char *str, char *result, t_shell *minishell)
{
	if (str[indices->i + 1] == '\0')
	{
		result[minishell->j++] = '$';
		minishell->i++;
	}
	else
	{
		process_special_dollar_cases(str, result, minishell);
	}
}

void	process_character(char *str, char *result, t_shell *minishell)
{
	if (str[indices->i] == '\"')
	{
		minishell->i++;
	}
	else if (str[minishell->i] == '\'')
	{
		result[minishell->j++] = str[minishell->i++];
	}
	else if (str[minishell->i] == '$')
	{
		process_dollar_character(str, result, minishell);
	}
	else
	{
		result[minishell->j] = str[minishell->i];
		minishell->j++;
		minishell->i++;
	}
	result[minishell->j] = '\0';
}
