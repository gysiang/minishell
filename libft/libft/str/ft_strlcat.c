/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:22 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:53:24 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	isize;

	isize = 0;
	while (*dst && isize < size)
	{
		isize++;
		dst++;
	}
	while (*src && isize + 1 < size)
	{
		*dst++ = *src++;
		isize++;
	}
	if (isize < size)
		*dst = '\0';
	while (*src++)
		isize++;
	return (isize);
}
