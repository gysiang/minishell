/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:14:31 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 20:15:25 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t count)
{
	char	*ptr;

	ptr = dest;
	while (*ptr)
		ptr++;
	while (*src && count > 0)
	{
		*ptr = *src;
		ptr++;
		src++;
		count--;
	}
	*ptr = '\0';
	return (dest);
}
