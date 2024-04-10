/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:15 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:53:18 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	is1;
	size_t	is2;
	char	*dest;
	char	*tdest;

	if (!s1 || !s2)
		return (NULL);
	is1 = ft_strlen(s1);
	is2 = ft_strlen(s2);
	dest = (char *)malloc((is1 + is2 + 1) * sizeof(char));
	if (!dest)
		return (dest);
	tdest = dest;
	while (*s1)
		*tdest++ = *s1++;
	while (*s2)
		*tdest++ = *s2++;
	*tdest = '\0';
	return (dest);
}
