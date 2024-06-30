/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes_utils_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:34:27 by axlee             #+#    #+#             */
/*   Updated: 2024/06/30 20:25:27 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_var_name(char *str, t_shell *minishell, char *var_name,
		int *var_len)
{
	while (ft_isalnum(str[minishell->i]) || str[minishell->i] == '_')
		var_name[(*var_len)++] = str[minishell->i++];
	var_name[*var_len] = '\0';
}

void	handle_digit_case(char *str, char **result, t_shell *minishell)
{
	minishell->i++;
	while (str[minishell->i] != '\0' && str[minishell->i] != ' ')
		(*result)[minishell->j++] = str[minishell->i++];
}

void	remove_trailing_double_quote(char **result, t_shell *minishell)
{
	if (minishell->j > 0 && (*result)[minishell->j - 1] == '"')
	{
		(*result)[minishell->j - 1] = '\0';
		minishell->j--;
	}
}

void	handle_env_variable_expansion(char *str, char **result,
		t_shell *minishell)
{
	char	var_name[256];
	char	*var_value;
	int		var_len;

	var_len = 0;
	minishell->i++;
	if (str[minishell->i] == '\0')
	{
		append_to_result(result, minishell, "$");
		return ;
	}
	if (!isdigit(str[minishell->i]))
	{
		extract_var_name(str, minishell, var_name, &var_len);
		var_value = get_env_value(minishell, var_name, 1);
		if (var_value)
			handle_variable_value(result, minishell, var_value);
		else
			handle_variable_not_found(result, minishell, var_name);
	}
	else
		handle_digit_case(str, result, minishell);
	remove_trailing_double_quote(result, minishell);
}
