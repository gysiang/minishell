/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes_utils_3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:06:08 by axlee             #+#    #+#             */
/*   Updated: 2024/06/12 13:54:36 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_exit_status(char **result, t_shell *minishell)
{
	char	exit_status[12];
	int		length;

	length = ft_sprintf(exit_status, "%d", minishell->last_return);
	if (length > 0)
	{
		ft_strcpy(&(*result)[minishell->j], exit_status);
		minishell->j += ft_strlen(exit_status);
	}
	minishell->i += 2;
}

void	process_special_characters(char *str, char **result, t_shell *minishell)
{
	char	next_char;

	next_char = str[minishell->i + 1];
	(*result)[minishell->j++] = '$';
	(*result)[minishell->j++] = next_char;
	minishell->i += 2;
}

void	process_dollar_followed_by_quote(char **result, t_shell *minishell)
{
	(*result)[minishell->j++] = '$';
	minishell->i++;
}

void	process_special_dollar_cases(char *str, char **result,
		t_shell *minishell)
{
	char	next_char;

	next_char = str[minishell->i + 1];
	if (next_char == '?')
		process_exit_status(result, minishell);
	else if (!ft_isalnum(next_char) && next_char != '_' && next_char != '\"')
		process_special_characters(str, result, minishell);
	else if (next_char == '\"')
		process_dollar_followed_by_quote(result, minishell);
	else
		handle_env_variable_expansion(str, result, minishell);
}

void	process_dollar_character(char *str, char **result, t_shell *minishell)
{
	if (str[minishell->i + 1] == '\0')
	{
		(*result)[minishell->j++] = '$';
		minishell->i++;
	}
	else
		process_special_dollar_cases(str, result, minishell);
}
