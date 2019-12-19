/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intprinters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 01:34:05 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/19 01:14:03 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** This function retrieves a decimal integer passed as an argument and converts
** it to a string using ft_itoa.
**
** The function divides all integers into four format categories:
** 1. No filler, just the number.
** 2. Number with spaces.
** 3. Number with zeros on the left.
** 4. Number with spaces and with zeros on the left.
**
** If g_flags.minwidth is less than or equal to the number length and the number
** length is greater than or equal to g_flags.maxwidth, then it must be case 1.
** If g_flags.minwidth is greater than the number length and the number length
** is greater than or equal to g_flags.maxwidth, then it must be case 2. If
** these cases are ruled out, then out of the remaining possible cases, if
** g_flags.minwidth is less than or equal to g_flags.maxwidth, it must be case
** 3. Otherwise (g_flags minwidth is greater than g_flags.maxwidth), it must be
** case 4.
**
** The function formats the number according to the identified format category.
**
** If the integer is negative, the function subtracts 1 from the measured
** strlen, under the assumption that the minus sign from the ft_itoa value will
** be skipped over and the printer functions will handle adding it back in where
** appropriate. However, if the case is no filler, the full ft_itoa string will
** be sent to be printed. In cases with spaces, 1 space will be subtracted from
** the assigned number of spaces for positive numbers to make room for the minus
** sign. In cases of only zeros on the left as filler, one will be added to the
** return value of bytes printed, as no zeros are deleted for the minus sign and
** the minus is still added before the zeros. In mixed space/zero cases, a space
** will be subtracted from the total to make room for the minus sign.
*/

int	ft_intprinter(long long int num, char *numstr)
{
	int	strlen;
	int	bytes;

	strlen = num < 0 ? (ft_strlen(numstr) - 1) : ft_strlen(numstr);
	if (num == 0 && g_flags.maxwidth == 0 && g_flags.usrdef && !g_flags.punt)
		ft_filler(' ', bytes = g_flags.minwidth);
	else if (g_flags.minwidth <= strlen && strlen >= g_flags.maxwidth)
		bytes = ft_putstr(numstr, (num < 0 ? strlen + 1 : strlen));
	else if (g_flags.minwidth > strlen && strlen >= g_flags.maxwidth)
		bytes = ft_onlyspaces(numstr, strlen, (g_flags.minwidth - strlen));
	else if (g_flags.minwidth <= g_flags.maxwidth)
		bytes = ft_onlyzeros(numstr, strlen);
	else
		bytes = ft_spacesandzeros(numstr, strlen);
	free(numstr);
	return (bytes);
}

int	ft_onlyspaces(char *str, int strlen, size_t fillwidth)
{
	int	bytes;

	bytes = g_flags.minwidth;
	fillwidth = g_flags.neg ? fillwidth - 1 : fillwidth;
	if (g_flags.dash)
	{
		if (g_flags.neg)
			write(1, "-", 1);
		ft_putstr((g_flags.neg ? &str[1] : str), strlen);
		ft_filler(' ', fillwidth);
	}
	else
	{
		if (!g_flags.zero || g_flags.usrdef)
			ft_filler(' ', fillwidth);
		if (g_flags.neg)
			write(1, "-", 1);
		if (g_flags.zero && !g_flags.usrdef)
			ft_filler('0', fillwidth);
		ft_putstr((g_flags.neg ? &str[1] : str), strlen);
	}
	return (bytes);
}

int	ft_onlyzeros(char *str, int strlen)
{
	if (g_flags.neg)
		write(1, "-", 1);
	if (g_flags.punt)
	{
		write(1, "0x", 2);
		str = str + 2;
		strlen = strlen - 2;
	}
	ft_filler('0', (g_flags.maxwidth - strlen));
	ft_putstr((g_flags.neg ? &str[1] : str), strlen);
	if (g_flags.neg)
		return (g_flags.maxwidth + 1);
	else if (g_flags.punt)
		return (g_flags.maxwidth + 2);
	else
		return (g_flags.maxwidth);
}

int	ft_spacesandzeros(char *str, int strlen)
{
	int	bytes;
	int	fillwidth;

	bytes = g_flags.minwidth;
	fillwidth = g_flags.neg ? (g_flags.minwidth - strlen - \
			(g_flags.maxwidth - strlen)) - 1 : g_flags.minwidth - strlen - \
			(g_flags.maxwidth - strlen);
	if (g_flags.dash)
	{
		if (g_flags.neg)
			write(1, "-", 1);
		ft_filler('0', (g_flags.maxwidth - strlen));
		ft_putstr((g_flags.neg ? &str[1] : str), strlen);
		ft_filler(' ', fillwidth);
	}
	else
	{
		ft_filler(' ', fillwidth);
		if (g_flags.neg)
			write(1, "-", 1);
		ft_filler('0', (g_flags.maxwidth - strlen));
		ft_putstr((g_flags.neg ? &str[1] : str), strlen);
	}
	return (bytes);
}
