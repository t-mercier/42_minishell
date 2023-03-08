/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 14:39:13 by asaijers      #+#    #+#                 */
/*   Updated: 2022/11/29 14:54:40 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"

int	_printf_hex(va_list vl)
{
	unsigned int	p;
	char			*s;
	int				n;

	p = va_arg(vl, unsigned int);
	s = _printf_ultoa(p, "0123456789abcdef");
	n = _printf_putstr(s);
	free(s);
	return (n);
}

int	_printf_hexupper(va_list vl)
{
	unsigned int	p;
	char			*s;
	int				n;

	p = va_arg(vl, unsigned int);
	s = _printf_ultoa(p, "0123456789ABCDEF");
	n = _printf_putstr(s);
	free(s);
	return (n);
}

int	_printf_dec(va_list vl)
{
	int		a;
	char	*s;
	int		n;

	a = va_arg(vl, int);
	s = _printf_sltoa(a, 0, "0123456789");
	n = _printf_putstr(s);
	free(s);
	return (n);
}

int	_printf_unsigned(va_list vl)
{
	unsigned int	a;
	char			*s;
	int				n;

	a = va_arg(vl, unsigned int);
	s = _printf_sltoa(a, 0, "0123456789");
	n = _printf_putstr(s);
	free(s);
	return (n);
}

int	ft_vprintf(const char *fmt, va_list vl)
{
	char	*a;
	int		n;

	a = (char *)fmt;
	n = 0;
	while (*a)
	{
		if (*a == '%')
		{
			a++;
			n += _printf_call(*a, vl);
			if (*a == '%')
				n += write(STDOUT_FILENO, "%", 1);
		}
		else
			n += write(STDOUT_FILENO, a, 1);
		if (*a)
			a++;
	}
	return (n);
}
