/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printftests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 23:42:36 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/19 04:52:12 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "libftprintf.h"

/*
 * %c/C - char
 * %s - string
 * %p - void (pointer addresses, display in hex)
 * %d/D - entero decimal
 * %i - entero decimal
 * %u - unsigned
 * %x - hex (minúsculas)
 * %X - hex (mayúsculas)
 *
 * flags
 * por defecto justifica a la derecha
 * - justifica a la izquierda
 * 0 - rellena de ceros hasta el mínimo
 * número positivo - ancho mínimo
 * .número positivo - ancho máximo
 * * pasar anccho mínimo/máximo desde fuera como argumento:
 * *integer value or * that specifies minimum field width. The result is padded with space characters (by default), if required, on the left when right-justified, or on the right if left-justified. In the case when * is used, the width is specified by an additional argument of type int. If the value of the argument is negative, it results with the - flag specified and positive field width. (Note: This is the minimum width: The value is never truncated.)

 '.' followed by integer number or '*', or neither that specifies precision of the conversion. In the case when * is used, the precision is specified by an additional argument of type int. If the value of this argument is negative, it is ignored. If neither a number nor * is used, the precision is taken as zero. See the table below for exact effects of precision.

 Máximo parece prevalecer sobre mínimo en mis pruebas...
*/

#include "libft.h"

int	main(void)
{
	char c = 'c';
	char *str = "str";
	int	d = 42;
	int i = 42;
	int qn = 3;
	unsigned int u = 42;
	int x = 0x4a;
	int X = 0x4A;
	int xadd = 0x6 + 0x6;
	int Xadd = 0x6 + 0x6;
	int xadd2 = 0x4f + 0x4b;
	int Xadd2 = 0x4F + 0x4B;
	int	*q = &qn;

	/*printf("1 %%c:\t\t%C\n", c);
	printf("2 %%s:\t\t%-3.1s\n", str);
	printf("3 %%p:\t\t%-20p\n", str);
	printf("4 %%D:\t\t%03D\n", d);
	printf("5 %%I:\t\t%i\n", i);
	printf("6 %%u:\t\t%u\n", u);
	printf("7 %%x:\t\t%x %X\n", x, x);
	printf("8 %%X:\t\t%x %X\n", X, X);
	printf("9 %%xadd:\t%x %x\n", xadd, Xadd);
	printf("10 %%Xadd:\t%X %X\n", xadd, Xadd);
	printf("11 %%xadd2:\t%x %x\n", xadd2, Xadd2);
	printf("12 %%Xadd2:\t%X %X\n", Xadd2, Xadd2);
//	printf("13 Nullantesdel\0final"); //Compilar con -w
//	printf("14 \t\t%010.010s\n", "nuevechar");
	printf("15 Max a min, igualico que en la mía...%1.-10cy no imprime flags =). \n", 'd');
	printf("16 Múltiples flags %.19%%s%y ahora qué?\n", "test");
	i = printf("17 Chartest: De momento%010cno es más que\n", 'd');
	printf("17.5 Size of 17 es: %d\n", i);
	i = printf("19 %*s|\n", -10, NULL);
	printf("19.5 Size of 19 es: %d\n", i);
	i= printf("20 %.5d|\n", -4242);
	printf("20.5 Size of 20 es: %d\n", i);
	printf("21 ^.^/%49c^.^/\n", 'g');
	i = printf("21.5 Size of 21 es: %d\n", i);
	i = printf("%.16lld", -440432320);
	 printf("\nSize of último es: %d\n", i);
	 i = printf("%0*d", 10, 42);
	 printf("\nSize of último  es: %d\n", i);
	i = printf("%-5.d", 0);
   printf("\nSize of último es: %d\n", i);
   i = printf("%-3d", 0);
   printf("\n%d\n", i);
   i = printf("%03.*d", -15, 1);
   printf("\n%d\n", i); 
   printf("\n%.0d\n", 0, 0);
  printf("%-8.3d\n", 0);*/
 i = printf("%");
 printf("\n%d\n", i);

/* int test = 42;

 char *testptr = test;

 printf("%zu", sizeof(*testptr));*/

	return (0);
}
