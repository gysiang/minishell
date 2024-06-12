/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:36:54 by axlee             #+#    #+#             */
/*   Updated: 2024/06/12 12:43:10 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	process_format_specifier(char **format, va_list *args, char *str,
		int *written)
{
	int		num;
	char	*p;
	char	buffer[12];

	num = va_arg(*args, int);
	p = ft_itoa(num);
	ft_strcpy(buffer, p);
	free(p);
	p = buffer;
	while (*p)
	{
		str[*written] = *p;
		(*written)++;
		p++;
	}
	*format += 2;
}

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	args;
	int		written;

	written = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1) == 'd')
		{
			process_format_specifier((char **)&format, &args, str, &written);
		}
		else
		{
			str[written] = *format;
			written++;
			format++;
		}
	}
	str[written] = '\0';
	va_end(args);
	return (written);
}
