/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes_utils_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:04:18 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 00:35:28 by gyong-si         ###   ########.fr       */
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
		t_shell *minishell, t_indices *indices)
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
			strcpy(&result[indices->j], exit_status);
			indices->j += strlen(exit_status);
		}
		indices->i += 2;
	}
	else if (!ft_isalnum(next_char) && next_char != '_' && next_char != '\"')
	{
		result[indices->j++] = '$';
		result[indices->j++] = next_char;
		indices->i += 2;
	}
	else if (next_char == '\"')
	{
		result[indices->j++] = '$';
		indices->i++;
	}
	else
	{
		handle_env_variable_expansion(str, minishell, indices, result);
	}
}

void	process_dollar_character(char *str, char *result, t_shell *minishell,
		t_indices *indices)
{
	if (str[indices->i + 1] == '\0')
	{
		result[indices->j++] = '$';
		indices->i++;
	}
	else
	{
		process_special_dollar_cases(str, result, minishell, indices);
	}
}

void	process_character(char *str, char *result, t_shell *minishell,
		t_indices *indices)
{
	if (str[indices->i] == '\"')
	{
		indices->i++;
	}
	else if (str[indices->i] == '\'')
	{
		result[indices->j++] = str[indices->i++];
	}
	else if (str[indices->i] == '$')
	{
		process_dollar_character(str, result, minishell, indices);
	}
	else
	{
		result[indices->j] = str[indices->i];
		indices->j++;
		indices->i++;
	}
	result[indices->j] = '\0';
}
