/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preppers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 23:34:04 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 14:31:01 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

/*
** This function initializes all global flags at zero. It is called whenever
** a new flag indicator ('%') is found, unless found within a format string.
**
** Dash tracks when a '-' flag is detected.
** Zero tracks when a '0' flag is detected.
** Astr tracks when a '*' flag is detected.
** Prec tracks when a '.' flag is detected.
** Neg tracks when a negative number is passed as an argument.
** Usrdef tracks when stored precision values are user defined.
** Ptr tracks when a pointer type is specified to apply special formatting.
** Pct tracks when a '%' is found within the format string.
** Minwidth stores the specified width.
** Maxwidth stores the specified precision.
*/

void	ft_flaginit(void)
{
	g_flags.dash = 0;
	g_flags.zero = 0;
	g_flags.astr = 0;
	g_flags.prec = 0;
	g_flags.neg = 0;
	g_flags.hash = 0;
	g_flags.plus = 0;
	g_flags.sp = 0;
	g_flags.apos = 0;
	g_flags.usrdef = 0;
	g_flags.ptr = 0;
	g_flags.pct = 0;
	g_flags.minwidth = 0;
	g_flags.maxwidth = 0;
	g_lenspec.l = 0;
	g_lenspec.ll = 0;
	g_lenspec.h = 0;
	g_lenspec.hh = 0;
}

/*
** This function prepares integers for formatting and printing by ft_intprinter.
** The value is extracted from the argument in the global argument list and
** stored in a local variable num. If negative, the appropriate flag is set.
** Ft_itoa is used to convert the integer into a string. The string is then
** passed to ft_intprinter for formatting and printing.
*/

int		ft_intprep(void)
{
	char			*numstr;
	long long int	num;

	num = ft_intextract();
	if (num < 0)
	{
		g_flags.neg = 1;
		g_flags.plus = 0;
		g_flags.sp = 0;
	}
	else if (!num && !g_flags.maxwidth && g_flags.usrdef && \
			(g_flags.plus || g_flags.sp))
	{
		if (g_flags.minwidth)
			return (ft_spacesorzeros((g_flags.plus ? "+" : " "), 1, \
			g_flags.minwidth));
			write(1, (g_flags.plus ? "+" : " "), 1);
		return (1);
	}
	numstr = ft_intwrite(num);
	numstr = ft_numstrprep(numstr);
	return (ft_intprinter(num, numstr));
}

/*
** This function prepares unsigned integers for formatting and printing by
** ft_intprinter. The value is extracted from the argument in the global
** argument list and stored in a local variable num.  Ft_llitoa is used to
** convert the integer into a string. The string is then passed to ft_intprinter
** for formatting and printing.
*/

int		ft_uintprep(void)
{
	char					*numstr;
	unsigned long long int	num;

	num = ft_uintextract();
	numstr = ft_uintwrite(num);
	numstr = ft_unumstrprep(numstr);
	return (ft_intprinter((long long int)num, numstr));
}

/*
** This function prepares hexadecimal numbers passed as unsigned integers for
** formatting and printing by ft_intprinter. The value is extracted from the
** argument in the global argument list and stored in a local variable num.
** Ft_llitoa_base is used to convert the integer into a hex string; by default,
** upper case letters are used. If a lower case 'x' is passed as conversion
** specifier (cs), ft_strtolower is used to convert the upper case letters in
** the string to lower case letters. The string is then passed to ft_intprinter
** for formatting and printing.
*/

int		ft_xintprep(char cs)
{
	char					*numstr;
	unsigned long long int	num;

	num = ft_uintextract();
	if (!num && g_flags.maxwidth == 0 && g_flags.usrdef && g_flags.hash)
		numstr = ft_strdup((cs == 'x' ? "0x" : "0X"));
	else if (!num && !g_flags.usrdef && g_flags.hash)
		return (ft_intprinter((long long int)num, (numstr = ft_strdup("0"))));
	else
		numstr = ft_xintprefixhandler(num, cs);
	return ((cs == 'p' || (g_flags.hash && (cs == 'x' || cs == 'X'))) ? \
			ft_xintprinter((unsigned long long int)num, numstr, cs) : \
			ft_intprinter((long long int)num, numstr));
}

/*
** This function prepares hexadecimal numbers defined as pointer addresses and
** passed as unsigned long integers for formatting and printing by
** ft_intprinter. The value is extracted from the argument in the global
** argument list and stored in a local variable num. The pointer flag is set
** to activate special pointer formatting.
**
** If the number passed is 0 and a user-defined 0 precision is detected, the
** string is defined as "0x". If the number passed is UINT_MAX, the string is
** defined as UINT_MAX in hexadecimal (ft_llitoa base will not do this on its
** own).
**
** Otherwise, ft_llitoa_base is used to convert the integer into a hex
** string, and the upper case letters it returns by default are converted to
** lower case with ft_strtolower. The value from ft_llitoa base is appended to
** "Ox" with ft_strjoin and its memory is then freed, while the concatenated
** value will become the new number string.
**
** In any case, the string is then passed to ft_intprinter for formatting and
** printing.
*/

int		ft_pintprep(char cs)
{
	char				*numstr;
	char				*del;
	unsigned long int	num;

	num = va_arg(g_arglst.arg, unsigned long int);
	g_flags.ptr = 1;
	if (!num && g_flags.maxwidth == 0 && g_flags.usrdef)
		numstr = ft_strdup("0x");
	else if (num == 18446744073709551615u)
		numstr = ft_strdup("0xffffffffffffffff");
	else
	{
		numstr = ft_llitoa_base((long long int)num, 16);
		del = numstr;
		ft_strtolower(numstr);
		numstr = ft_strjoin("0x", numstr);
		free(del);
	}
	return (ft_xintprinter((unsigned long long int)num, numstr, cs));
}
