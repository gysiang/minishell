/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:21:54 by axlee             #+#    #+#             */
/*   Updated: 2024/03/13 17:21:57 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define TRUE 1
# define FALSE 0

# include <stdarg.h>
# include "libft.h"

typedef struct s_flags
{
	int		justify;
	int		plus;
	int		invisible_plus;
	int		zerofill;
	int		width;
	int		precision;
	int		precision_n;
	int		zero_x;
	int		specifier;
	int		params_length;
	char	*params;
}			t_flags;

t_flags	flag_parse(const char *s);
int		ft_printf(const char *arr, ...);
char	*c_format_string(va_list args, t_flags flags);
char	*s_format_string(va_list args, t_flags flags);
char	*p_format_string(va_list args, t_flags flags);
char	*d_format_string(va_list args, t_flags flags);
char	*u_format_string(va_list args, t_flags flags);
char	*x_format_string(va_list args, t_flags flags);

#endif