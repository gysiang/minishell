/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:50:43 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:50:48 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	add_char(char **str, char c)
{
	char	*ret;
	char	*tmp;

	ret = malloc (2 * sizeof(char));
	ret[0] = c;
	ret[1] = '\0';
	tmp = ft_strjoin(*str, ret);
	free (ret);
	free (*str);
	*str = tmp;
	return (1);
}

void	invert_str(char *src, char **dest)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[0][i] = src[ft_strlen(src) - i - 1];
		i++;
	}
	dest[0][i] = '\0';
}
