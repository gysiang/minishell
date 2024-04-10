/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:48:56 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:48:59 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;

	d = dest;
	if (!src && !dest)
		return (NULL);
	while (n > 0)
	{
		*(char *)d = *(char *)src;
		d++;
		src++;
		n--;
	}
	return (dest);
}
