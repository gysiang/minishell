/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:44 by axlee             #+#    #+#             */
/*   Updated: 2024/06/03 13:24:31 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strccmp(const char *s1, const char *s2, char c)
{
    size_t  i;

    i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] == c || s2[i] == c)
            return (s1[i] - s2[i]);
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (s1[i] - s2[i]);
}
