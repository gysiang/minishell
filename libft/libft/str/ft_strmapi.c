/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:39 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:53:41 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*ret;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	ret = malloc((len + 1) * sizeof(char));
	i = 0;
	if (ret)
	{
		while (*s)
		{
			ret[i] = (*f)(i, *s);
			s++;
			i++;
		}
		ret[i] = '\0';
	}
	return (ret);
}
