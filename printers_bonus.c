/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 03:26:57 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 13:54:22 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Prints the argument and then filler, or the filler and then the argument,
** depending on whether the dash ('-') flag has been set. Fillwidth filler
** characters are printed.
**
** If the specified width is greater than the string length and the string
** length is less than the specified precision value, strlen bytes (the
** entire string) are printed; otherwise (string length is longer than
** the minimum width or longer than the precision value), only up to precision
** value bytes of the string are printed.
**
** The filler goes after the text string if the dash ('-') flag is active (to
** justify the text left); otherwise, it goes before to justify the text
** right.
**
** If the zero ('0') flag has been set and the dash ('-') flag has not been set,
** zeros are printed as filler, otherwise spaces are printed. That is, zeros can
** only be printed as filler for right-justified text.
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

void	ft_wfoutput(wchar_t *str, int strlen, size_t fillwidth)
{
	if (g_flags.dash)
	{
		ft_putstr((char const *)str, (g_flags.minwidth > strlen && \
					strlen < g_flags.maxwidth ? strlen : g_flags.maxwidth));
		ft_filler(' ', fillwidth);
	}
	else
	{
		ft_filler((g_flags.zero ? '0' : ' '), fillwidth);
		ft_putstr((char const *)str, (g_flags.minwidth > strlen && \
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
	wint_t			c;

	c = ft_charextract();
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
** Prints the current argument passed as a string. Precision determmines the
** number of string bytes to be printed. Width determines the amount of
** printable space, and will always be at least the string length.
**
** If a precision value of zero has been set by the user, an empty string is
** passed and the argument is not retrieved, but the  next argument in the
** global argument list is called.
**
** If the argument to be formatted is a NULL pointer, "(null)" is passed.
**
** Otherwise, a character pointer to the argument is passed.
**
** Note that if a user-defined precision value has not been set, the
** precision value here defaults to strlen.
**
** Strings are divided into two case types.
**
** 1. Just the string, or part of it, is printed. No filler spaces/zeros.
** 2. The string, or part of it, is printed with filler spaces/zeros.
**
** Case 1 occurs when specified width is less than or equal to strlen and
** strlen is less than or equal to the precision value or when width is
** less than strlen and strlen is greater than the precision value, and
** at the same time width is greater than or equal to the precision value.
**
** Case 2 covers all other cases.
**
** For case 1, if the string length is less than or equal to the
** specified precision value, then it is printed in its entirety. Otherwise
** precision value characters are printed from the string (it's truncated).
**
** For case 2, ft_foutput is called to handle the formatting with fillers
** The amount of filler will be the specified width minus the strlen, which
** occupies width spaces, if width is greater than the strlen and the
** strlen is less than the precision width (meaning the string will not
** be truncated). That is to say, if the whole string must be printed, it
** will be width - string length. Otherwise, if the string must be
** truncated, it will be width - the precision value (which, due to
** truncation, becomes the effective string length, so it's still the same
** logic).
**
** The function returns bytes printed. In case 1, this will be the
** precision value if the string was truncated, and strlen if it was
** not. In case 2, this will always be the specified minimum width.
**
** Note: strlen is now called 'len', (thanks Norminette ¬¬).
*/

int		ft_strprinter(void)
{
	char			*str;
	int				len;
	int				fillwidth;

	str = ft_strextract();
	len = ft_strlen(str);
	g_flags.maxwidth = g_flags.prec && g_flags.usrdef ? g_flags.maxwidth : len;
	if ((g_flags.minwidth <= len && len <= g_flags.maxwidth) || \
	((g_flags.minwidth < len && len > g_flags.maxwidth) && \
	(g_flags.minwidth <= g_flags.maxwidth)))
	{
		ft_putstr(str, (len <= g_flags.maxwidth ? len : g_flags.maxwidth));
		return (g_flags.minwidth < len && len > g_flags.maxwidth ? \
				g_flags.maxwidth : len);
	}
	else
	{
		fillwidth = g_flags.minwidth > len && len < g_flags.maxwidth ? \
				g_flags.minwidth - len : g_flags.minwidth - g_flags.maxwidth;
		ft_foutput(str, len, fillwidth);
	}
	return (g_flags.minwidth);
}

int		ft_wstrprinter(void)
{
	wchar_t			*str;
	int				len;
	int				fillwidth;

	str = ft_wstrextract();
	len = ft_wstrlen(str);
	g_flags.maxwidth = g_flags.prec && g_flags.usrdef ? g_flags.maxwidth : len;
	if ((g_flags.minwidth <= len && len <= g_flags.maxwidth) || \
	((g_flags.minwidth < len && len > g_flags.maxwidth) && \
	(g_flags.minwidth <= g_flags.maxwidth)))
	{
		ft_putstr((char const *)str, (len <= g_flags.maxwidth ? \
					len : g_flags.maxwidth));
		return (g_flags.minwidth < len && len > g_flags.maxwidth ? \
				g_flags.maxwidth : len);
	}
	else
	{
		fillwidth = g_flags.minwidth > len && len < g_flags.maxwidth ? \
				g_flags.minwidth - len : g_flags.minwidth - g_flags.maxwidth;
		ft_wfoutput(str, len, fillwidth);
	}
	return (g_flags.minwidth);
}
