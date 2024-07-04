/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:33:32 by axlee             #+#    #+#             */
/*   Updated: 2024/07/04 16:43:01 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quotes_for_trim(const char *str, int *in_quotes,
		char *quote_char, int i)
{
	if ((str[i] == '"' || str[i] == '\'') && !(*in_quotes))
	{
		*in_quotes = 1;
		*quote_char = str[i];
	}
	else if (str[i] == *quote_char && *in_quotes)
		*in_quotes = 0;
}

char	*ft_strtrim_preserve_quotes(char *str, char *set)
{
	int		start;
	int		end;
	int		in_quotes;
	char	quote_char;
	int		i;

	start = 0;
	end = ft_strlen(str) - 1;
	in_quotes = 0;
	quote_char = 0;
	while (str[start] && ft_strchr(set, str[start]))
		start++;
	while (end > start && ft_strchr(set, str[end]))
		end--;
	i = start;
	while (i <= end)
	{
		handle_quotes_for_trim(str, &in_quotes, &quote_char, i);
		i++;
	}
	return (ft_substr(str, start, end - start + 1));
}
