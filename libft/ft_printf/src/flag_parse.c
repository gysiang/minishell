/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:20:16 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:20:19 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_specification(char c)
{
	char	*specs;

	specs = "cspdiuxX%";
	if (ft_strchr(specs, c))
		return (1);
	else
		return (-1);
}

static int	is_flag(char c, t_flags *flags)
{
	if (c == '-')
		flags->justify = TRUE;
	else if (c == '0'
		&& flags->width == FALSE
		&& flags->precision == FALSE
		&& flags->justify == FALSE)
		flags->zerofill = 48;
	else if (c == '+')
		flags->plus = TRUE;
	else if (c == ' ')
		flags->invisible_plus = TRUE;
	else if (c == '#')
		flags->zero_x = TRUE;
	else
		return (0);
	return (1);
}

static int	is_precision(char c, t_flags *flags)
{
	if (c == '.')
	{
		flags->precision = TRUE;
		flags->zerofill = 32;
	}
	else if (ft_isdigit(c) && flags->precision == TRUE)
	{
		if (flags->precision_n == 0)
			flags->precision_n = c - 48;
		else
			flags->precision_n = (flags->precision_n * 10) + (c - 48);
	}
	else if (ft_isdigit(c) && flags->precision != TRUE)
	{
		if (flags->width == 0)
			flags->width = c - 48;
		else
			flags->width = (flags->width * 10) + (c - 48);
	}
	else
		return (0);
	return (1);
}

static void	init_struct(t_flags *flags)
{
	flags->justify = 0;
	flags->plus = 0;
	flags->invisible_plus = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->precision_n = 0;
	flags->zerofill = 32;
	flags->zero_x = 0;
	flags->specifier = 0;
	flags->params_length = 0;
	flags->params = ft_strdup("%");
}

t_flags	flag_parse(const char *s)
{
	int		i;
	t_flags	flags;

	i = 0;
	init_struct(&flags);
	while (is_flag(s[i], &flags) || is_precision(s[i], &flags))
	{
		add_char(&flags.params, s[i]);
		i++;
	}
	if (is_specification(s[i]) > 0)
		flags.specifier = s[i];
	else
		flags.specifier = 'E';
	add_char(&flags.params, s[i]);
	flags.params_length = i + 1;
	return (flags);
}
