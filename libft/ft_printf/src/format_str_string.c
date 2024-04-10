/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:21:12 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:21:15 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*format_str_width(char *str, t_flags flags)
{
	int		size;
	int		str_len;
	char	*ret;

	str_len = ft_strlen(str);
	if ((int)str_len >= flags.width)
		size = ft_strlen(str);
	else
		size = flags.width;
	ret = ft_calloc ((size + 1), sizeof(char));
	ft_memset(ret, 32, size);
	ft_memcpy(ret + ((!flags.justify) * (size - str_len)), str, str_len);
	ret[size] = '\0';
	return (ret);
}

static char	*format_str_precision(char *str, t_flags flags)
{
	int		size;
	int		str_len;
	char	*ret;

	if (!flags.precision)
		return (ft_strdup(str));
	str_len = ft_strlen(str);
	size = str_len;
	if (flags.precision && flags.precision_n < str_len)
		size = flags.precision_n;
	ret = ft_calloc((size + 1), sizeof(char));
	ft_memcpy(ret, str, size);
	return (ret);
}

char	*s_format_string(va_list args, t_flags flags)
{
	char	*str;
	char	*tmp;
	char	*ret;

	str = ft_strdup(va_arg(args, char *));
	if (!str)
		str = ft_strdup("(null)");
	tmp = format_str_precision(str, flags);
	ret = format_str_width(tmp, flags);
	free (str);
	free (tmp);
	return (ret);
}

char	*c_format_string(va_list args, t_flags flags)
{
	int		size;
	int		i;
	char	c;
	char	*ret;

	c = va_arg(args, int);
	size = 1;
	i = 0;
	if (flags.width > 1)
		size = flags.width;
	ret = malloc ((size + 1) * sizeof(char));
	ft_memset(ret, 32, size);
	ret[((!flags.justify) * (size - 1))] = c;
	ret[size] = '\0';
	while (i < size)
	{
		ft_putchar_fd(ret[i], 1);
		i++;
	}
	if (c == '\0')
		ret[((!flags.justify) * (size - 1))] = '0';
	return (ret);
}
