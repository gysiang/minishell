/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sutils_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:29:38 by axlee             #+#    #+#             */
/*   Updated: 2024/06/13 12:51:11 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_get_size(void *ptr)
{
	if (ptr == NULL)
		return (0);
	return (*((size_t *)ptr - 1));
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	old_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	old_size = ft_get_size(ptr);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}
