/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:23:56 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 13:48:42 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** This function sets the appropriate flags when width and/or precision
** (maxwidth) is set via additional arguments using the asterisk ('*')
** flag.
*/

void		ft_argwidthflags(char const *format)
{
	*format == '.' ? (g_flags.maxwidth = va_arg(g_arglst.arg, int)) : \
						(g_flags.minwidth = va_arg(g_arglst.arg, int));
	g_flags.dash = g_flags.minwidth < 0 || g_flags.maxwidth < 0 ? \
						1 : g_flags.dash;
	g_flags.minwidth = g_flags.minwidth < 0 ? g_flags.minwidth * -1 : \
							g_flags.minwidth;
	g_flags.usrdef = *format == '.' && g_flags.maxwidth >= 0 ? 1 : 0;
	g_flags.maxwidth = g_flags.maxwidth < 0 ? 0 : g_flags.maxwidth;
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

int			ft_widthparser(char const *format)
{
	size_t	i;
	size_t	len;
	char	*width;

	i = 0;
	len = 0;
	width = format[i] == '.' ? (char *)&format[++i] : (char *)&format[i];
	g_flags.usrdef = *format == '.' ? 1 : g_flags.usrdef;
	if (format[i] == '*')
	{
		ft_argwidthflags(format);
		return (*format == '.' ? 2 : 1);
	}
	while (format[i] && ft_isdigit(format[i++]))
		len++;
	if (!(width = ft_substr(width, 0, len)))
		return (-1);
	*format != '.' ? (g_flags.minwidth = ft_atoi(width)) : \
					(g_flags.maxwidth = ft_atoi(width));
	g_flags.usrdef = *format == '.' && len > 0 ? 1 : g_flags.usrdef;
	g_flags.usrdef = (*format == '.' && ((ft_isdigit(format[1])))) ? \
						1 : g_flags.usrdef;
	free(width);
	return (*format != '.' ? len : len + 1);
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

	flaglst = "%-.*#+ 'lh0123456789";
	i = 0;
	ft_flaginit();
	while ((ft_strchr(flaglst, format[i])) && format[i])
	{
		if (format[i] == '%')
			break ;
		else if (format[i] == '0' || ((!(ft_isdigit(format[i])) && \
				format[i] != '.' && format[i] != '*')))
			ft_flagchecker(format[i++]);
		else
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
