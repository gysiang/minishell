/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:49:05 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:49:07 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;

	if (src < dest)
	{
		d = dest + n - 1;
		src += n - 1;
		while (n > 0)
		{
			*(char *)d = *(char *)src;
			d--;
			src--;
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
