/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:29 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:53:31 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	i;

	if (!dst || !src)
		return (0);
	i = ft_strlen(src);
	if (size == 0)
		return (i);
	while (*src && size > 0)
	{
		*dst++ = *src++;
		size--;
	}
	if (size == 0)
		dst--;
	*dst = '\0';
	return (i);
}
