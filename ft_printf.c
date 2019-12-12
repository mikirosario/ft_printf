/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 02:22:12 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/12 04:00:57 by mrosario         ###   ########.fr       */
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

unsigned long	ft_converter(char cs)
{
	if (cs == 'c' || cs == 'C')
		return (ft_charprinter());
	else if (cs == 's')
		return (ft_strprinter());
	return (0);
}

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
		if (*format == '.')
			g_flags.maxwidth = va_arg(g_arglst.arg, int);
		else
			g_flags.minwidth = va_arg(g_arglst.arg, int);
		return (*format == '.' ? 2 : 1);
	}
	while (format[i] && ft_isdigit(format[i++]))
		len++;
	if (!(width = ft_substr(width, 0, len)))
		return (-1);
	if (*format != '.')
		g_flags.minwidth = ft_atoi(width);
	else
		g_flags.maxwidth = ft_atoi(width);
	free(width);
	return (*format != '.' ? len : len + 1);
}

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
			if ((skip = ft_widthparser(&format[i])) == -1)
				return (NULL);
			else
				i = i + skip;
		}
	}
	return (&format[i]);
}

int	ft_printf(char const *format, ...)
{
	//char *ptr;
	char *conv;
	char *cslst;

	g_flags.minwidth = 0;
	g_bytes = 0;
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
	printf("Min Width: %u | Max Width: %u | Bytes: %lu | '0' = %d | '-' = %d\n", g_flags.minwidth, g_flags.maxwidth, g_bytes, g_flags.zero, g_flags.dash);
	/*ptr = (va_arg(g_arglst.arg, char *));
	while (*ptr)
		ft_putchar(*ptr++);
*/
	va_end(g_arglst.arg);

	return (g_bytes);
}
