/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:49 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:53:51 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	ilittle;

	ilittle = ft_strlen(little);
	if (!ilittle)
		return ((char *)big);
	if (ilittle > ft_strlen(big))
		return (NULL);
	while (*big && len)
	{
		if (ilittle > ft_strlen(big) || len < ilittle)
			return (NULL);
		if (ft_strncmp(big, little, ilittle) == 0 && len >= ilittle)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
