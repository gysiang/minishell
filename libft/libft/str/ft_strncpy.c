/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:24:39 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 20:27:47 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < count)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
