/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intprinters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 01:34:05 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 14:28:14 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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

int	ft_intprinter(long long int num, char *numstr)
{
	int	strlen;
	int	bytes;

	strlen = num < 0 || g_flags.plus || g_flags.sp ? \
				(ft_strlen(numstr) - 1) : ft_strlen(numstr);
	if (num == 0 && g_flags.maxwidth == 0 && g_flags.usrdef && !g_flags.ptr)
		ft_filler(' ', bytes = g_flags.minwidth);
	else if (g_flags.minwidth <= strlen && strlen >= g_flags.maxwidth)
		bytes = ft_putstr(numstr, (num < 0 || g_flags.plus || g_flags.sp ? \
				strlen + 1 : strlen));
	else if (g_flags.minwidth > strlen && strlen >= g_flags.maxwidth)
		bytes = ft_spacesorzeros(numstr, strlen, (g_flags.minwidth - strlen));
	else if (g_flags.minwidth <= g_flags.maxwidth)
		bytes = ft_onlyzeros(numstr, strlen);
	else
		bytes = ft_spacesandzeros(numstr, strlen);
	free(numstr);
	return (bytes);
}

/*
** This function will format integer strings that only need to be formatted with
** a static number of spaces or zeros determined by the fill width (space not
** occupied by the string proper).
***
** The amount of filler that needs to be printed is given by width - strlen, as
** strlen takes up spaces of a given minimum width. For negative numbers it
** will be width - strlen - 1 to make room for the minus sign.
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

int	ft_spacesorzeros(char *str, int strlen, size_t fillwidth)
{
	int	bytes;

	bytes = g_flags.minwidth;
	fillwidth = g_flags.neg || g_flags.plus || \
				g_flags.sp ? fillwidth - 1 : fillwidth;
	if (g_flags.dash)
	{
		if (g_flags.neg)
			write(1, "-", 1);
		if (g_flags.plus || g_flags.sp)
			write(1, (g_flags.plus ? "+" : " "), 1);
		ft_putstr((g_flags.neg || g_flags.plus || \
					g_flags.sp ? &str[1] : str), strlen);
		ft_filler(' ', fillwidth);
	}
	else
	{
		ft_spacesorhelper(str, strlen, fillwidth);
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

int	ft_onlyzeros(char *str, int strlen)
{
	if (g_flags.neg)
		write(1, "-", 1);
	if (g_flags.plus || g_flags.sp)
		write(1, (g_flags.plus ? "+" : " "), 1);
	ft_filler('0', (g_flags.maxwidth - strlen));
	ft_putstr((g_flags.neg || g_flags.plus || \
				g_flags.sp ? &str[1] : str), strlen);
	if (g_flags.neg || g_flags.plus || g_flags.sp)
		return (g_flags.maxwidth + 1);
	else
		return (g_flags.maxwidth);
}

/*
** This function will handle mixed cases in which both spaces and zeros
** will need to be printed. Hexadecimal numbers that prepend '0x' will
** be diverted to ft_hexspacesandzeros.
**
** The amount of zeros that need to be printed will always be the
** specified precision - strlen (as in ft_onlyzeros).
**
** The amount of spaces that need to be printed will be indicated by
** the variable 'fillwidth'. This will be equal to
** width - strlen - (precision value - strlen). That is to say,
** subtracting both the number proper and any zeros to be printed
** from the minimum width, or, in other words, both strlen and padded
** zeros will use up minimum width space.
**
** The value will be justified left or right depending on the dash ('-')
** flag status. The minus sign ('-') for negative numbers will always
** be written before any padded zeros, regardless of how the number is
** justified.
**
** The function returns bytes printed, which will always be 'width' bytes.
*/

int	ft_spacesandzeros(char *str, int strlen)
{
	int	bytes;
	int	fillwidth;

	bytes = g_flags.minwidth;
	fillwidth = g_flags.neg || g_flags.plus || g_flags.sp ? \
				(g_flags.minwidth - strlen - (g_flags.maxwidth - strlen)) \
				- 1 : g_flags.minwidth - strlen - \
			(g_flags.maxwidth - strlen);
	if (g_flags.dash)
	{
		if (g_flags.neg)
			write(1, "-", 1);
		if (g_flags.plus || g_flags.sp)
			write(1, (g_flags.plus ? "+" : " "), 1);
		ft_filler('0', (g_flags.maxwidth - strlen));
		ft_putstr((g_flags.neg || g_flags.plus || \
				g_flags.sp ? &str[1] : str), strlen);
		ft_filler(' ', fillwidth);
	}
	else
	{
		ft_spacesandhelper(str, strlen, fillwidth);
	}
	return (bytes);
}
