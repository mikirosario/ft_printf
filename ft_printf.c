/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 02:22:12 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/19 20:22:40 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Takes string passed as format and parses it, printing and counting
** all characters until a '%' or '\0' is found. If a '\0' is found
** printing terminates. Counted characters are stored in the global
** variable bytes.
**
** If a '%' is found, ft_flagparser is executed and passed the address
** of the following character of the string format to search for format
** flags to apply to any variadic arguments passed to printf;
** ft_flagparser returns the address of the character following the last
** character that it handled, which is then passed directly to the pointer
** format. Characters handled by ft_flagparser are not counted by bytes.
** If ft_flagparser returns a NULL pointer, ft_printf returns -1 to signal
** that there has been an error.
**
** After ft_flagparser terminates, the character dereferenced by *format is
** checked against the conversion specifier characters stored in the string
** cslst. If there is a match, ft_converter is executed and passed the
** identified conversion specifier to initiate necessary operations for
** printing the current argument in the variadic argument list g_arglst.arg.
** Ft_converter returns the number of bytes printed. These bytes are added
** to bytes.
*/

int			ft_printf(char const *format, ...)
{
	char	*cs;
	char	*cslst;
	int		bytes;

	bytes = 0;
	cslst = "cCsdDiupxX%";
	va_start(g_arglst.arg, format);
	while (*format)
	{
		*format != '%' ? bytes++ : *format;
		*format != '%' ? ft_putchar(*format++) : *format;
		if (*format == '%')
		{
			if (!(format = ft_flagparser(++format)))
				return (-1);
			else if ((cs = ft_strchr(cslst, *format)) && *format)
			{
				g_flags.pct = *format == '%' ? 1 : g_flags.pct;
				bytes = bytes + (ft_converter(*cs));
				format++;
			}
		}
	}
	va_end(g_arglst.arg);
	return (bytes);
}
