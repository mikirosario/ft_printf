/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 02:22:12 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 08:51:10 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Takes string passed as format and parses it, printing and counting
** all characters until a '%' or '\0' is found. If a '\0' is found
** printing terminates. Counted characters are stored in the variable
** bytes, which is returned upon function termination. If there is a
** memory allocation failure at any point during runtime, -1 is
** returned.
**
** If a '%' is found, ft_flagparser is executed and passed the address
** of the following character of the string 'format' to search for format
** flags to apply to any variadic arguments passed to printf;
** ft_flagparser returns the address of the character following the last
** character that it handled, which is then used to redirect the pointer
** 'format'. Characters handled by ft_flagparser are thus not counted by
** the variable 'bytes' or printed by the function ft_printf.
**
** After ft_flagparser terminates, the character dereferenced by *format
** after ft_flagparser redirects the pointer 'format' to the next unhandled
** byte is checked against the conversion specifier characters stored in the
** string cslst. If there is a match, ft_converter is executed and passed
** the identified conversion specifier to initiate necessary operations for
** printing the current argument in the global variadic argument list
** g_arglst.arg.
**
** Ft_converter returns the number of argument bytes printed by the
** functions it calls to handle the specified argument type. These bytes are
** then added to the variable bytes.
*/

int			ft_printf(char const *format, ...)
{
	char	*cs;
	char	*cslst;

	g_bytes = 0;
	cslst = "cCsdDiupxXn%";
	va_start(g_arglst.arg, format);
	while (*format)
	{
		*format != '%' ? g_bytes++ : *format;
		*format != '%' ? ft_putchar(*format++) : *format;
		if (*format == '%')
		{
			if (!(format = ft_flagparser(++format)))
				return (-1);
			else if ((cs = ft_strchr(cslst, *format)) && *format)
			{
				ft_lencheck((*(format - 1)), (*(format - 2)));
				g_flags.pct = *format == '%' ? 1 : g_flags.pct;
				g_bytes = g_bytes + (ft_converter(*cs));
				format++;
			}
		}
	}
	va_end(g_arglst.arg);
	return (g_bytes);
}
