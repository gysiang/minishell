/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:52:54 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:52:58 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	is;

	is = ft_strlen(s);
	while (*s != (char)c && is-- > 0)
		s++;
	if (!*s && c)
		return (NULL);
	return ((char *)s);
}
