/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:21:21 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:21:25 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*form_string(va_list args, t_flags flags)
{
	char	*ret;

	if (flags.specifier == 'c')
		ret = c_format_string(args, flags);
	else if (flags.specifier == 's')
		ret = s_format_string(args, flags);
	else if (flags.specifier == 'p')
		ret = p_format_string(args, flags);
	else if (flags.specifier == 'd' || flags.specifier == 'i')
		ret = d_format_string(args, flags);
	else if (flags.specifier == 'u')
		ret = d_format_string(args, flags);
	else if (flags.specifier == 'x' || flags.specifier == 'X')
		ret = x_format_string(args, flags);
	else if (flags.specifier == '%')
		ret = ft_strdup("%");
	else
		ret = NULL;
	return (ret);
}

static int	format_handler(const char **s, va_list args, int *i)
{
	char	*ret;
	t_flags	flags;

	flags = flag_parse(*s);
	if (flags.specifier == 'E')
		return (-1);
	ret = form_string(args, flags);
	if (!ret)
		return (flags.params_length);
	*i += ft_strlen(ret);
	if (flags.specifier != 'c')
		ft_putstr_fd(ret, 1);
	free (ret);
	free (flags.params);
	return (flags.params_length);
}

int	ft_printf(const char *arr, ...)
{
	va_list	args;
	int		i;
	int		ret;

	i = 0;
	va_start(args, arr);
	while (*arr)
	{
		if (*arr == '%')
		{
			arr++;
			ret = format_handler(&arr, args, &i);
			if (ret < 0)
				return (-1);
			arr += ret;
		}
		else
		{
			ft_putchar_fd(*arr, 1);
			i++;
			arr++;
		}
	}
	va_end(args);
	return (i);
}
