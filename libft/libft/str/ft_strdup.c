/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:03 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:53:05 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*pret;

	if (!s)
		return (NULL);
	pret = malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!pret)
		return (NULL);
	ft_strlcpy(pret, s, (ft_strlen(s) + 1));
	return (pret);
}
