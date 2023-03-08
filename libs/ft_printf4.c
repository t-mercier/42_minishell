/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:42:05 by asaijers      #+#    #+#                 */
/*   Updated: 2022/11/04 15:56:01 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"

size_t	_printf_strlen(const char *s)
{
	const char	*a;

	a = s;
	while (*s)
		s++;
	return (s - a);
}

void	*_printf_memcpy(void *dst, const void *src, size_t n)
{
	char		*a;
	const char	*b;

	if (!dst && !src)
		return (0);
	a = dst;
	b = src;
	while (n--)
		a[n] = b[n];
	return (dst);
}

char	*_printf_strdup(char *s)
{
	size_t	n;
	void	*d;

	n = _printf_strlen(s) + 1;
	d = malloc(n);
	if (!d)
		return (0);
	return (_printf_memcpy(d, s, n));
}

char	*_printf_sltoa(long n, int o, char *base)
{
	char	_x[100];
	char	*x;
	size_t	bl;

	bl = _printf_strlen(base);
	x = _x;
	x += 99;
	*x-- = 0;
	o = 0;
	if (n < 0)
	{
		o = 1;
		n = -n;
	}
	if (!n)
		*x-- = base[0];
	while (n)
	{
		*x-- = base[n % bl];
		n /= bl;
	}
	if (o)
		*x-- = '-';
	x++;
	return (_printf_strdup(x));
}

char	*_printf_ultoa(unsigned long n, char *base)
{
	char	_x[100];
	char	*x;
	size_t	bl;

	bl = _printf_strlen(base);
	x = _x;
	x += 99;
	*x-- = 0;
	if (!n)
		*x-- = base[0];
	while (n)
	{
		*x-- = base[n % bl];
		n /= bl;
	}
	x++;
	return (_printf_strdup(x));
}
