/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:06:40 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 11:11:20 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(const char *content)
{
	int		len;
	char	*var_name;

	len = 0;
	while (content[len] && content[len] != '=')
		len++;
	var_name = ft_strndup(content, len);
	return (var_name);
}

int	is_valid_identifier(const char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	create_env_entry(char *dest, const char *var_name,
		const char *var_value)
{
	while (*var_name)
		*dest++ = *var_name++;
	*dest++ = '=';
	while (*var_value)
		*dest++ = *var_value++;
	*dest = '\0';
}