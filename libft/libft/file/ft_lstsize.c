/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:41:25 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:45:35 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*tracker;

	if (!lst)
		return (-1);
	counter = 0;
	tracker = lst->next;
	while (tracker)
	{
		tracker = tracker->next;
		counter++;
	}
	return (counter);
}
