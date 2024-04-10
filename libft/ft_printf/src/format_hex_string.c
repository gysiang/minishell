/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_hex_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:20:42 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:20:45 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*zero_x(char *str, t_flags flags)
{
	char	*ret;

	if (*str == '0' && ft_strlen(str) == 1)
		ret = ft_strdup(str);
	else if (flags.zero_x && flags.specifier == 'x')
		ret = ft_strjoin("0x", str);
	else if (flags.zero_x && flags.specifier == 'X')
		ret = ft_strjoin("0X", str);
	else
		ret = ft_strdup(str);
	return (ret);
}

char	*format_hex_width(char *str, t_flags flags, int nbr)
{
	int		size;
	int		str_len;
	char	*tmp;
	char	*ret;

	if (nbr)
		tmp = zero_x(str, flags);
	else
		tmp = ft_strdup(str);
	str_len = ft_strlen(tmp);
	if (str_len >= flags.width)
		size = str_len;
	else
		size = flags.width;
	ret = ft_calloc((size + 1), sizeof(char));
	ft_memset(ret, flags.zerofill, size);
	ft_memcpy(ret + ((!flags.justify) * (size - str_len)), tmp, str_len);
	ret[size] = '\0';
	if (flags.zero_x && flags.zerofill == 48 && flags.width > str_len)
	{
		ret[1] = tmp[1];
		ret[ft_strlen(ret) - str_len + 1] = 48;
	}
	free (tmp);
	return (ret);
}

char	*format_hex_precision(char *str, t_flags flags)
{
	int		size;
	int		str_len;
	char	*ret;

	if (!flags.precision)
		return (ft_strdup(str));
	str_len = ft_strlen(str);
	size = str_len;
	if (flags.precision && flags.precision_n > str_len)
		size = flags.precision_n;
	ret = ft_calloc((size + 1), sizeof(char));
	ft_memset(ret, 48, size);
	ft_memcpy(ret + (size - str_len), str, str_len);
	return (ret);
}

char	*x_format_string(va_list args, t_flags flags)
{
	char			*str;
	char			*tmp;
	char			*ret;
	unsigned int	lint;

	lint = va_arg(args, unsigned int);
	if (lint == 0 && flags.precision && !flags.precision_n)
		str = ft_strdup("");
	else if (flags.specifier == 'x')
		str = ft_nbr_base(lint, "0123456789abcdef");
	else
		str = ft_nbr_base(lint, "0123456789ABCDEF");
	tmp = format_hex_precision(str, flags);
	ret = format_hex_width(tmp, flags, lint);
	free (str);
	free (tmp);
	return (ret);
}

char	*p_format_string(va_list args, t_flags flags)
{
	char	*arg;
	char	*str;
	char	*prec;
	char	*tmp;
	char	*ret;

	arg = va_arg(args, char *);
	if (!arg)
		str = ft_strdup("0");
	else
		str = ft_ullnbr_base((unsigned long long)arg, "0123456789abcdef");
	prec = format_hex_precision(str, flags);
	tmp = ft_strjoin("0x", prec);
	ret = format_hex_width(tmp, flags, 1);
	free (prec);
	free (tmp);
	free (str);
	return (ret);
}
