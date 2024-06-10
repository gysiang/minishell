/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:33:25 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/10 12:38:57 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if character is space
int	ft_iswhitespace(char *line)
{
	if (*line == ' ')
		return (1);
	return (0);
}

int	ft_isbackslash(char *line)
{
	if (*line == '\\')
		return (1);
	return (0);
}

int	ft_issemicolon(char *line)
{
	if (*line == ';')
		return (1);
	return (0);
}

char	*ft_copy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*ptr)
		ptr++;
	while (*src)
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return (dest);
}
