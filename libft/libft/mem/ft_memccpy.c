/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:48:28 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:48:33 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n > 0)
	{
		ft_memcpy(dest, src, sizeof(char));
		if (*(unsigned char *)src == (unsigned char)c)
			return (dest + 1);
		dest++;
		src++;
		n--;
	}
	return (NULL);
}
