/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:22:08 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/03 13:22:21 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strcat(char *dst, const char *src)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(dst[i])
        i++;
    while(src[j])
        dst[i++] = src[j++];
    dst[i] = '\0';
    return (dst);
}
