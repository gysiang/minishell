/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes_utils_1.c                      :+:      :+:    :+:   */
/*                                                    +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:46:06 by axlee             #+#    #+#             */
/*   Updated: 2024/06/09 20:49:45 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_special_env_variable(char *result, t_shell *minishell)
{
	char	*expanded;
	int		i;
	int		j;

	i = 0;
	j = 0;
	expanded = ft_itoa(minishell->last_return);
	ft_strcpy(&result[j], expanded);
	j += ft_strlen(expanded);
	free(expanded);
	i += 2;
}

void	extract_variable_name(char *str, char **var_name, int *var_len)
{
	char	*var_start;
	char	*var_end;

	var_start = &str[1];
	var_end = var_start;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	*var_len = var_end - var_start;
	*var_name = ft_strndup(var_start, *var_len);
}

void	handle_regular_env_variable(char *str, char *result, t_shell *minishell)
{
	char	*var_name;
	char	*expanded;
	int		var_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	extract_variable_name(str, &var_name, &var_len);
	expanded = get_env_value(minishell, var_name, 1);
	if (expanded)
	{
		ft_strcpy(&result[j], expanded);
		j += ft_strlen(expanded);
	}
	i += var_len;
	free(var_name);
}
