/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 03:26:57 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/19 04:47:52 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Prints the argument and then filler, or the filler and then the argument,
** depending on whether the dash flag has been set. Fillwidth filler characters
** are printed.
**
** If the specified minwidth is greater than the string length and the string
** length is less than the maxwidth specified by the precision ('.') flag,
** strlen bytes are printed, otherwise only up to maxwidth bytes are printed.
**
** If the zero ('0') flag has been set and the filler is printed before the
** argument, then 0s are printed instead of spaces, otherwise spaces are
** printed.
*/

void	ft_foutput(char *str, int strlen, size_t fillwidth)
{
	if (g_flags.dash)
	{
		ft_putstr(str, (g_flags.minwidth > strlen && \
					strlen < g_flags.maxwidth ? strlen : g_flags.maxwidth));
		ft_filler(' ', fillwidth);
	}
	else
	{
		ft_filler((g_flags.zero ? '0' : ' '), fillwidth);
		ft_putstr(str, (g_flags.minwidth > strlen && \
					strlen < g_flags.maxwidth ? strlen : g_flags.maxwidth));
	}
}

/*
** Prints arguments passed as characters.
**
** If a dash flag has been set, prints the argument passed as char and then
** width filler (by default, filler is ' '). If the dash flag has not been set
** (is 0), prints width filler, assigning '0' to filler if the zero flag has
** been set, and then the argument passed as char.
**
** Returns number of bytes printed.
*/

int		ft_charprinter(void)
{
	char			filler;
	int				width;
	int				c;

	c = g_flags.pct ? '%' : va_arg(g_arglst.arg, int);
	filler = ' ';
	width = g_flags.minwidth > 0 && g_flags.minwidth <= 2147483647 ? \
			g_flags.minwidth - 1 : 0;
	if (g_flags.dash)
	{
		write(1, &c, 1);
		while (width && width--)
			write(1, &filler, 1);
	}
	else
	{
		if (g_flags.zero)
			filler = '0';
		while (width && width--)
			write(1, &filler, 1);
		write(1, &c, 1);
	}
	return (g_flags.minwidth > 0 ? g_flags.minwidth : 1);
}

/*
** Prints current argument passed as string.
**
** If a dash flag has been set, outputs strlen or maxwidth (precision) chars
** from str, as appropriate (see case chart), then fills the remainder with
** spaces on the right. Otherwise fills fillwidth spaces with spaces, or
** with 0s if the zero flag has been set, and then outputs either strlen or
** maxwidth chars on the right, as appropriate.
**
** Returns number of bytes printed.
*/

int		ft_strprinter(void)
{
	char			*str;
	int				strlen;
	int				fillwidth;

	if (!(str = va_arg(g_arglst.arg, char *)))
		str = "(null)";
	strlen = ft_strlen(str);
	g_flags.maxwidth = g_flags.prec && g_flags.usrdef ? g_flags.maxwidth : strlen;
	if ((g_flags.minwidth <= strlen && strlen <= g_flags.maxwidth) ||
			((g_flags.minwidth < strlen && strlen > g_flags.maxwidth) && \
			(g_flags.minwidth <= g_flags.maxwidth)))
	{
		ft_putstr(str, (strlen <= g_flags.maxwidth ? \
					strlen : g_flags.maxwidth));
		return (g_flags.minwidth < strlen && strlen > g_flags.maxwidth ? \
				g_flags.maxwidth : strlen);
	}
	else
	{
		fillwidth = g_flags.minwidth > strlen && strlen < g_flags.maxwidth ? \
					g_flags.minwidth - strlen : \
					g_flags.minwidth - g_flags.maxwidth;
		ft_foutput(str, strlen, fillwidth);
	}
	return (g_flags.minwidth);
}
