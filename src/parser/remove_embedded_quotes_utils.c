/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_embedded_quotes_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:10:47 by axlee             #+#    #+#             */
/*   Updated: 2024/06/09 13:28:35 by axlee            ###   ########.fr       */
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
	int		new_len;
	char	*new_str;
	int		i;
	int		j;

	new_len = len - 2;
	new_str = (char *)malloc(new_len + 1);
	j = 0;
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (i != first_quote_index && i != last_quote_index)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[new_len] = '\0';
	return (new_str);
}
