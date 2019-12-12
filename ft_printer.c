/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 03:26:57 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/12 19:25:44 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** If a dash flag has been set, outputs strlen or maxwidth (precision) chars
** from str, as appropriate (see case chart), then fills the remainder with
** spaces on the right. Otherwise fills fillwidth spaces with spaces, or
** with 0s if the zero flag has been set, and then outputs either strlen or
** maxwidth chars on the right, as appropriate.
*/

void			ft_foutput(char *str, size_t strlen, size_t fillwidth)
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

unsigned long	ft_charprinter(void)
{
	char			filler;
	size_t			width;
	int				c;

	c = va_arg(g_arglst.arg, int);
	filler = ' ';
	width = g_flags.minwidth > 0 && g_flags.minwidth <= 4294967295 ? \
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

unsigned long	ft_strprinter(void)
{
	char			*str;
	unsigned int	strlen;
	unsigned int	fillwidth;

	str = va_arg(g_arglst.arg, char *);
	strlen = ft_strlen(str);
	if ((g_flags.minwidth <= strlen && strlen <= g_flags.maxwidth) ||
			(g_flags.minwidth < strlen && strlen > g_flags.maxwidth))
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
