/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 02:22:12 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/16 06:50:31 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * %c/C - char
 * %s - string
 * %p - void (pointer addresses, display in hex)
 * %d/D - entero decimal
 * %i - entero decimal
 * %u - unsigned
 * %x - hex (minúsculas)
 * %X - hex (mayúsculas)
 *
 * flags
 * por defecto justifica a la derecha
 * - justifica a la izquierda
 * 0 - rellena de ceros hasta el mínimo
 * número positivo - ancho mínimo
 * .número positivo - ancho máximo
 * * pasar anccho mínimo/máximo desde fuera como argumento:
 * *integer value or * that specifies minimum field width. The result is padded with space characters (by default), if required, on the left when right-justified, or on the right if left-justified. In the case when * is used, the width is specified by an additional argument of type int. If the value of the argument is negative, it results with the - flag specified and positive field width. (Note: This is the minimum width: The value is never truncated.)

 '.' followed by integer number or '*', or neither that specifies precision of the conversion. In the case when * is used, the precision is specified by an additional argument of type int. If the value of this argument is negative, it is ignored. If neither a number nor * is used, the precision is taken as zero. See the table below for exact effects of precision.

 Máximo parece prevalecer sobre mínimo en mis pruebas...
*/

#include "libftprintf.h"
#include <stdio.h>

/*
** Receives conversion specifier (cs) and executes the function appropriate
** to the received cs.
**
** Returns the value returned by the executed function, which corresponds to
** the number of bytes ultimately printed.
*/

unsigned long	ft_converter(char cs)
{
	if (cs == 'c' || cs == 'C')
		return (ft_charprinter());
	else if (cs == 's')
		return (ft_strprinter());
	else if (cs == 'd' || cs == 'D' || cs == 'i')
		return (ft_intprinter());
	return (0);
}

/*
** This function handles numerical flags (minwidth, precision, asterisk).
** Parses the string passed via the pointer format searching for digits. If
** a dot flag ('.') is found as the first element, the derived value will
** be taken as maxwidth; otherwise, the derived value will be taken as
** minwidth. The value is derived by counting all string characters (or all
** characters after the dot flag, as appropriate) until a non-digit is
** found, and then extracting a substring of the length of the counted
** digits. The substring is then sent to ft_atoi to be converted into an
** int, which will be the derived value. If an asterisk flag ('*') is found,
** then the value of the current argument taken y va_arg is passed directly
** to minwidth or maxwidth, as appropriate; if this value is negative, then
** it is made positive before being passed and the minus sign is interpreted
** as a dash flag ('-'), which is then set.
**
** Returns the number of bytes parsed as flags so they can be skipped. If
** memory allocation fails, -1 is returned.
*/

int		ft_widthparser(char const *format)
{
	size_t	i;
	size_t	len;
	char	*width;

	i = 0;
	len = 0;
	width = format[i] == '.' ? (char *)&format[++i] : (char *)&format[i];
	if (format[i] == '*')
	{
		*format == '.' ? (g_flags.maxwidth = va_arg(g_arglst.arg, int)) : \
						(g_flags.minwidth = va_arg(g_arglst.arg, int));
		g_flags.dash = g_flags.minwidth < 0 || g_flags.maxwidth < 0 ? 1 : 0;
		g_flags.minwidth = g_flags.minwidth < 0 ? g_flags.minwidth * -1 : \
							g_flags.minwidth;
		g_flags.maxwidth = g_flags.maxwidth < 0 ? g_flags.maxwidth * -1 : \
							g_flags.maxwidth;
		return (*format == '.' ? 2 : 1);
	}
	while (format[i] && ft_isdigit(format[i++]))
		len++;
	if (!(width = ft_substr(width, 0, len)))
		return (-1);
	*format != '.' ? (g_flags.minwidth = ft_atoi(width)) : \
					(g_flags.maxwidth = ft_atoi(width));
	free(width);
	return (*format != '.' ? len : len + 1);
}

/*
** Checks the passed character against the list of flags, and sets
** the flags to true, as appropriate.
*/

int		ft_flagchecker(char f)
{
	if (f == '%')
	{
		ft_putchar(f);
		g_bytes++;
	}
	else if (f == '-')
		g_flags.dash = 1;
	else if (f == '0')
		g_flags.zero = 1;
	return (f == '%' ? 1 : 0);
}

/*
** Parses the string passed via the pointer format looking for flags
** in the string flaglst. If a character in flaglst is identified in
** the string format, either ft_flagchecker or ft_widthparser is
** executed, depending on whether the identified char is a '%', '-'
** or '0' (first if), or any digit except 0, '.' or '*' (else if).
** If ft_flagchecker finds a '%' flag it returns '1', which causes
** the while loop to break and the function to return the address of
** the following char.
**
** If a precision flag ('.') is found, this flag is set to true and
** the following character is assumed to be numerical and has its
** address passed to ft_widthparser for examination. If
** ft_widthparser is run, it returns the number of characters it has
** parsed, which is stored in the int skip, and then added to the
** index int i so that they are not parsed again.
**
** The function parses through the string format until either a
** '%' or any other char not in flaglst is found, at which point
** it terminates the parsing loop.
**
** This function returns the address of the character in the string
** passed via the pointer format that caused the parsing loop to be
** broken (the first non-flag char or '%' flag). If ft_widthparser
** returns -1 it means that memory allocation failed. In this case a
** NULL pointer is returned.
*/

char const	*ft_flagparser(char const *format)
{
	int			i;
	int			skip;
	char		*flaglst;

	flaglst = "%-.*0123456789";
	i = 0;
	while ((ft_strchr(flaglst, format[i])))
	{
		if (format[i] == '%' || format[i] == '-' || format[i] == '0')
		{
			if (ft_flagchecker(format[i++]))
				break ;
		}
		else if ((ft_isdigit(format[i]) && format[i] != '0') ||
				format[i] == '.' || format[i] == '*')
		{
			if (format[i] == '.')
				g_flags.prec = 1;
			if ((skip = ft_widthparser(&format[i])) == -1)
				return (NULL);
			else
				i = i + skip;
		}
	}
	return (&format[i]);
}

/*
** Takes string passed as format and parses it, printing and counting
** all characters until a '%' or '\0' is found. If a '\0' is found
** printing terminates. Counted characters are stored in the global
** variable g_bytes.
**
** If a '%' is found, ft_flagparser is executed and passed the address
** of the following character of the string format to search for format
** flags to apply to any variadic arguments passed to printf;
** ft_flagparser returns the address of the character following the last
** character that it handled, which is then passed directly to the pointer
** format. Characters handled by ft_flagparser are not counted by g_bytes.
** If ft_flagparser returns a NULL pointer, ft_printf returns -1 to signal
** that there has been an error.
**
** After ft_flagparser terminates, the character dereferenced by *format is
** checked against the conversion specifier characters stored in the string
** cslst. If there is a match, ft_converter is executed and passed the
** identified conversion specifier to initiate necessary operations for
** printing the current argument in the variadic argument list g_arglst.arg.
** Ft_converter returns the number of bytes printed. These bytes are added
** to g_bytes.
*/

int	ft_printf(char const *format, ...)
{
	//char *ptr;
	char *conv;
	char *cslst;

	g_bytes = 0;
	g_flags.dash = 0;
	g_flags.zero = 0;
	g_flags.astr = 0;
	g_flags.prec = 0;
	g_flags.neg = 0;
	g_flags.minwidth = 0;
	g_flags.maxwidth = 0;
	cslst = "cCsdDiupxX";
	va_start(g_arglst.arg, format);
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar(*format++);
			g_bytes++;
		}
		else
		{
			if (!(format = ft_flagparser(++format)))
				return (-1);
			if ((conv = ft_strchr(cslst, *format)))
			{
				g_bytes = g_bytes + (ft_converter(*conv));
				format++;
			}
		}
	}
	printf("Min Width: %ld | Max Width: %ld | Bytes: %lu | '0' = %d | '-' = %d | '.' = %d\n", g_flags.minwidth, g_flags.maxwidth, g_bytes, g_flags.zero, g_flags.dash, g_flags.prec);
	/*ptr = (va_arg(g_arglst.arg, char *));
	while (*ptr)
		ft_putchar(*ptr++);
*/
	va_end(g_arglst.arg);

	return (g_bytes);
}
