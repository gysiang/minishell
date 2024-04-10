/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:55 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:53:56 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	is;

	if (!*s && c)
		return (NULL);
	is = ft_strlen(s);
	if (c == 0)
	{
		s += is;
		return ((char *)s);
	}
	s += is - 1;
	while (*s != (char)c && is-- > 1)
		s--;
	if (is == 0)
		return (NULL);
	return ((char *)s);
}
