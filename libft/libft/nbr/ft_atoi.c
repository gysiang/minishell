/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:49:45 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:49:49 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long int	ret;
	int			signal;

	ret = 0;
	signal = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		ret *= 10;
		ret += *nptr - 48;
		nptr++;
		if (ret > 2147483647 && signal == 1)
			return (-1);
		if (ret > 2147483648 && signal == -1)
			return (0);
	}
	return ((int)ret * signal);
}
