/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexprinters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 11:18:14 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 14:18:46 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

/*
** This function takes an integer and a string representing that integer and
** prints the string with the format defined by the activated format flags.
**
** The function divides all integers into four format categories:
** 1. No filler, just the number.
** 2. Number with either spaces or zeros as filler.
** 3. Number with only zeros on the left as filler.
** 4. Number with spaces and with zeros on the left.
**
** If g_flags.minwidth is less than or equal to the number length and the number
** length is greater than or equal to g_flags.maxwidth, then it must be case 1.
**
** Otherwise, if g_flags.minwidth is greater than the number length and the
** number length is greater than or equal to g_flags.maxwidth, then it must be
** case 2.
**
** If both of these cases are ruled out, then out of the remaining possible
** cases:
**
** If g_flags.minwidth is less than or equal to g_flags.maxwidth, it must be
** case 3.
**
** Otherwise (g_flags minwidth is greater than g_flags.maxwidth), it
** must be case 4.
**
** The function formats the number according to the identified format category
** following this logic. See Readme for more details.
*/

int		ft_xintprinter(long long int num, char *numstr, char cs)
{
	int	strlen;
	int	bytes;

	strlen = (ft_strlen(numstr) - 1);
	if (num == 0 && g_flags.maxwidth == 0 && g_flags.usrdef && !g_flags.ptr)
		ft_filler(' ', bytes = g_flags.minwidth);
	else if (g_flags.minwidth <= strlen && strlen >= g_flags.maxwidth)
		bytes = ft_putstr(numstr, strlen + 2);
	else if (g_flags.minwidth > strlen && strlen >= g_flags.maxwidth)
		bytes = ft_hexspacesorzeros(numstr, strlen, \
				(g_flags.minwidth - strlen), cs);
	else if (g_flags.minwidth <= g_flags.maxwidth)
		bytes = ft_hexonlyzeros(numstr, strlen, cs);
	else
		bytes = ft_hexspacesandzeros(numstr, strlen, cs);
	free(numstr);
	return (bytes);
}

/*
** This function will format integer strings that only need to be formatted with
** a static number of spaces or zeros determined by the fill width (space not
** occupied by the string proper).
**
** The amount of filler that needs to be printed is given by minwidth - strlen,
** as strlen takes up spaces of a given minimum width.
**
** Note that in the original ft_intprinter 1 is subtracted from strlen before
** calling the equivalent ft_spacesorzeros function, and so enters that
** function with strlen - 1 compared to ft_hexspacesorzeros under the same
** conditions. Since fillwidth is minwidth - strlen, fillwidth is also
** worth 1 less than it is in ft_spacesorzeros under the same conditions.
**
** In the original ft_spacesorzeros 1 is subtracted from fillwidth to
** account for the single minus sign that the function inserts. In this case
** 1 must be *added* to fillwidth because, under the same conditions, *two*
** signs, rather than one, are inserted ('0x'). In this case the 0x is
** displaced leftward and an extra byte is counted, as signs are
** allowed to violate minwidth restrictions in printf.
**
** If the dash ('-') flag has been set, first the number and then the spaces
** will be printed. Otherwise, if the zero ('0') flag has not been set OR the
** precision value is user defined, spaces will be used followed by the number.
** Otherwise, if the zero flag has been set AND the precision value is not user
** defined (0 by default), zeros will be printed followed by the number.
**
** A minus sign is appended as necessary for negative numbers. It will go after
** spaces but always before zeros.
**
** Hexadecimal numbers displaying '0x' before their values have dynamic fill
** behaviour under these conditions as the '0x' is omitted in certain
** circumstances, and so will be diverted to ft_hexspacesandzeros for proper
** handling.
**
** The number of bytes printed is returned. This will always be width in this
** case.
*/

int		ft_hexspacesorzeros(char *str, int strlen, size_t fillwidth, char cs)
{
	int	bytes;

	bytes = g_flags.maxwidth == strlen ? \
			g_flags.minwidth + 1 : g_flags.minwidth;
	fillwidth -= 1;
	if (g_flags.dash)
	{
		write(1, (cs == 'X' ? "0X" : "0x"), 2);
		ft_putstr(&str[2], strlen);
		ft_filler(' ', fillwidth);
	}
	else
	{
		if ((!g_flags.zero || g_flags.usrdef) && fillwidth > 0)
			ft_filler(' ', fillwidth);
		write(1, (cs == 'X' ? "0X" : "0x"), 2);
		if (g_flags.zero && !g_flags.usrdef)
			ft_filler('0', fillwidth);
		ft_putstr(&str[2], strlen);
	}
	return (bytes);
}

/*
** This function will format integer strings that only need to be formatted with
** zeros.
**
** In this case, if the number is negative a minus sign is prefixed to
** it. As there are no spaces to delete to make room for it, the presence of a
** negative value will add 1 to the number of bytes printed. The function will
** write its own "-" minus sign as any padded zeros must be between the minus
** sign and the number proper.
**
** If the number is a pointer address, since padded zeros must go after "0x",
** the function will write its own "0x" and move the string pointer two places
** forward to skip the number string's native "0x", making sure to subtract 2
** from the reported 'strlen'. It will then append as many zeros as needed
** (always the precision value minus the string length) and print the number.
** If the number is negative, it is printed starting from the second value in
** the number string to skip the native minus sign.
**
** The amount of padding is determined by the precision value (maxwidth), but
** space will be taken from the specified precision value to make room for
** the number proper.
**
** The number of bytes printed is returned. For positive integers this will
** normally be the precision value. For negative integers, this will be the
** precision value + 1 to make room for the minus sign. For pointer
** addresses, this will be the precision value + 2 to make room for the "0x".
*/

int		ft_hexonlyzeros(char *str, int strlen, char cs)
{
	if ((str[2] != '0') || (g_flags.ptr || (g_flags.hash && \
		(cs == 'x' || cs == 'X'))))
	{
		if ((str[2] == '0' && cs == 'p') || str[2] != '0')
			write(1, (cs == 'X' ? "0X" : "0x"), 2);
		if (g_flags.ptr || (g_flags.hash && (cs == 'x' || cs == 'X')))
			strlen = strlen - 1;
	}
	ft_filler('0', (g_flags.maxwidth - strlen));
	ft_putstr(&str[2], strlen);
	if (g_flags.ptr || (g_flags.hash && (cs == 'x' || cs == 'X')))
		return (g_flags.maxwidth + 2);
	else
		return (g_flags.maxwidth);
}

/*
** Because hexadecimal numbers being printed with '0x' will sometimes
** omit the '0x' depending on the flags set and thus the zeros to be
** printed cannot be predicted by the original string width, as it
** may vary, they display dynamic fill behaviour.
**
** This function handles these cases similarly to ft_spacesandzeros.
*/

int		ft_hexspacesandzeros(char *str, int strlen, char cs)
{
	int	fillwidth;
	int	bytes;

	bytes = g_flags.minwidth;
	fillwidth = g_flags.minwidth - strlen;
	if (g_flags.maxwidth > strlen - 2 || \
		(!g_flags.usrdef && str[2] == '0' && cs != 'p'))
		fillwidth = fillwidth - (g_flags.maxwidth - 1);
	if (g_flags.dash)
	{
		if (str[2] != '0')
			write(1, (cs == 'X' ? "0X" : "0x"), 2);
		ft_filler('0', (g_flags.maxwidth - strlen + 1));
		ft_putstr(&str[2], strlen);
		ft_filler(' ', (str[2] == '0' ? fillwidth + 1 : fillwidth));
	}
	else
	{
		ft_hexspzerohelper(str, strlen, cs, fillwidth);
	}
	return (bytes);
}

void	ft_hexspzerohelper(char *str, int strlen, char cs, int fillwidth)
{
	str[2] == '0' ? fillwidth++ : fillwidth;
	if (!g_flags.zero || g_flags.usrdef)
		ft_filler(' ', fillwidth);
	if (str[2] != '0' || cs == 'p')
		write(1, (cs == 'X' ? "0X" : "0x"), 2);
	str[2] == '0' ? g_flags.maxwidth++ : g_flags.maxwidth;
	if (g_flags.zero || g_flags.maxwidth > strlen - 2)
		ft_filler('0', (g_flags.maxwidth > strlen - 2 ? \
		g_flags.maxwidth - 2 : fillwidth));
	ft_putstr(&str[2], strlen);
}
