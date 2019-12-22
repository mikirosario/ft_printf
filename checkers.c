/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 13:46:54 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 13:48:58 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** This function checks the two characters prior to the identified conversion
** specifier. If they match any of the available length specifiers, a flag
** is tripped that will change the type of the appropriate conversion
** specifier to long, long long, etc.
*/

void		ft_lencheck(char c1, char c2)
{
	char	prevchars[3];

	prevchars[0] = c1;
	prevchars[1] = c2;
	prevchars[2] = '\0';
	if (ft_strnstr(prevchars, "ll", 2))
		g_lenspec.ll = 1;
	else if (ft_strnstr(prevchars, "hh", 2))
		g_lenspec.hh = 1;
	else if (ft_strnstr(prevchars, "l", 2))
		g_lenspec.l = 1;
	else if (ft_strnstr(prevchars, "h", 2))
		g_lenspec.h = 1;
}

/*
** Receives conversion specifier (cs) and executes the function appropriate
** to the received cs.
**
** Returns the value returned by the executed function, which corresponds to
** the number of bytes ultimately printed.
*/

int			ft_converter(char cs)
{
	int	*n;

	if (g_flags.dash)
		g_flags.zero = 0;
	if (cs == 'c' || cs == 'C' || cs == '%')
		return (ft_charprinter());
	else if (cs == 's')
		return (g_lenspec.l ? ft_wstrprinter() : ft_strprinter());
	else if (cs == 'd' || cs == 'D' || cs == 'i')
		return (ft_intprep());
	else if (cs == 'u')
		return (ft_uintprep());
	else if (cs == 'p')
		return (ft_pintprep(cs));
	else if (cs == 'x' || cs == 'X')
		return (ft_xintprep(cs));
	else if (cs == 'n')
		if ((n = va_arg(g_arglst.arg, int *)))
			*n = g_bytes;
	return (0);
}

/*
** Checks the passed character against the list of flags, and sets
** the flags to true, as appropriate.
*/

void		ft_flagchecker(char f)
{
	if (f == '-')
		g_flags.dash = 1;
	else if (f == '0')
		g_flags.zero = 1;
	else if (f == '#')
		g_flags.hash = 1;
	else if (f == '+')
		g_flags.plus = 1;
	else if (f == ' ')
		g_flags.sp = 1;
	else if (f == '\'')
		g_flags.apos = 1;
}
