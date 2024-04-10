/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:47:25 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:47:28 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*del_member;
	t_list	*next_member;

	if (!lst)
		return ;
	del_member = *lst;
	while (del_member)
	{
		next_member = del_member->next;
		(*del)(del_member);
		free(del_member);
		del_member = next_member;
	}
	lst = NULL;
}
