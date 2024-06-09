/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_embedded_quotes_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:10:47 by axlee             #+#    #+#             */
/*   Updated: 2024/06/09 12:19:46 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_first_quote(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (i);
		i++;
	}
	return (-1);
}

int	find_last_quote(char *str, int len, int first_quote_index, char quote_char)
{
	int	i;

	i = len - 1;
	while (i > first_quote_index)
	{
		if (str[i] == quote_char)
			return (i);
		i--;
	}
	return (-1);
}

int	check_quotes_in_between(char *str, int first_quote_index,
		int last_quote_index, char quote_char)
{
	int	i;

	i = first_quote_index + 1;
	while (i < last_quote_index)
	{
		if (str[i] == quote_char)
			return (1);
		i++;
	}
	return (0);
}

char	*remove_quotes(char *str, int first_quote_index, int last_quote_index,
		int len)
{
	char	*new_str;

	new_str = malloc(len - 1);
	if (new_str == NULL)
		return (NULL);
	memcpy(new_str, str, first_quote_index);
	memcpy(new_str + first_quote_index, str + first_quote_index + 1,
		last_quote_index - first_quote_index - 1);
	memcpy(new_str + last_quote_index - 1, str + last_quote_index + 1, len
		- last_quote_index - 1);
	new_str[len - 2] = '\0';
	return (new_str);
}
