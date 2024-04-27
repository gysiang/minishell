/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:57:04 by axlee             #+#    #+#             */
/*   Updated: 2024/04/12 12:57:29 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_free(char ***str_array)
{
	size_t	i;

	i = 0;
	while ((*str_array)[i])
	{
		ft_strdel(&((*str_array)[i]));
		i++;
	}
	free(*str_array);
	*str_array = NULL;
}