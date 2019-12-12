/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 02:25:54 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/12 19:16:47 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFTPRINTF_H
# define FT_LIBFTPRINTF_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

typedef struct	s_flags
{
	int				dash;
	int				zero;
	int				astr;
	unsigned int	minwidth;
	unsigned int	maxwidth;
}				t_flags;

typedef struct	s_arglst
{
	va_list	arg;
}				t_arglst;

unsigned long	g_bytes;
t_flags			g_flags;
t_arglst		g_arglst;

int					ft_printf(char const *format, ...);
char const			*ft_flagparser(char const *format);
int					ft_flagchecker(char	f);
int					ft_widthparser(char const *width);
unsigned long		ft_converter(char cs);
unsigned long		ft_charprinter(void);
unsigned long		ft_strprinter(void);
void				ft_foutput(char *str, size_t strlen, size_t fillwidth);

// int	ft_minmax(int num);

#endif
