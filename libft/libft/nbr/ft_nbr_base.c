/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:50:20 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:50:23 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_base_is_valid(char *base)
{
	char	c;

	c = *base;
	base++;
	while (*base != '\0')
	{
		if (*base != c)
		{
			c = *base;
			base++;
		}
		else
			return (0);
	}
	return (1);
}

char	*ft_add_base(long long nbr, char *basec, long long basen)
{
	char	b;
	char	*invert;
	char	*ret;

	invert = ft_strdup("");
	if (nbr < basen)
		add_char(&invert, basec[nbr % basen]);
	while (nbr >= basen)
	{
		b = basec[nbr % basen];
		add_char(&invert, b);
		if (nbr / basen < basen)
		{
			b = basec[nbr / basen];
			add_char(&invert, b);
		}
		nbr = nbr / basen;
	}
	ret = malloc ((ft_strlen(invert) + 1) * sizeof(char));
	invert_str(invert, &ret);
	free (invert);
	return (ret);
}

char	*ft_nbr_base(long long nbr, char *base)
{
	char	*ret;
	char	*basec;
	int		i;

	i = 0;
	if (nbr == 0)
		return (ft_strdup("0"));
	basec = base;
	while (*basec != '\0')
	{
		basec++;
		i++;
	}
	if (!(i > 1))
		return (NULL);
	if (!ft_base_is_valid(base))
		return (NULL);
	ret = ft_add_base((unsigned long long)nbr, base, i);
	return (ret);
}

char	*ft_ulladd_base(unsigned long long nbr, char *basec, long long basen)
{
	char	b;
	char	*invert;
	char	*ret;

	invert = ft_strdup("");
	if (nbr < (unsigned long long)basen)
		add_char(&invert, basec[nbr % basen]);
	while (nbr >= (unsigned long long)basen)
	{
		b = basec[nbr % basen];
		add_char(&invert, b);
		if (nbr / basen < (unsigned long long)basen)
		{
			b = basec[nbr / basen];
			add_char(&invert, b);
		}
		nbr = nbr / basen;
	}
	ret = malloc ((ft_strlen(invert) + 1) * sizeof(char));
	invert_str(invert, &ret);
	free (invert);
	return (ret);
}

char	*ft_ullnbr_base(unsigned long long nbr, char *base)
{
	char	*ret;
	char	*basec;
	int		i;

	i = 0;
	if (nbr == 0)
		return (ft_strdup("0"));
	basec = base;
	while (*basec != '\0')
	{
		basec++;
		i++;
	}
	if (!(i > 1))
		return (NULL);
	if (!ft_base_is_valid(base))
		return (NULL);
	ret = ft_ulladd_base((unsigned long long)nbr, base, i);
	return (ret);
}
