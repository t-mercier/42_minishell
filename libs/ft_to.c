/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_to.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:11:08 by asaijers      #+#    #+#                 */
/*   Updated: 2022/10/10 14:33:47 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - 32);
	return (c);
}

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c + 32);
	return (c);
}

int	ft_atoi(const char *s)
{
	long long	n;
	int			o;

	n = 0;
	while (*s && ft_isspace(*s))
		s++;
	o = 0;
	if (*s == '-')
		o = 1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s && ft_isdigit(*s))
	{
		n *= 10;
		n += *s - '0';
		s++;
	}
	if (o)
		return (-n);
	return (n);
}

static char	*_ft_itoa(long long n, int o)
{
	char	_x[12];
	char	*x;

	x = _x;
	x += 11;
	*x-- = 0;
	o = 0;
	if (n < 0)
	{
		o = 1;
		n = -n;
	}
	if (!n)
		*x-- = '0';
	while (n)
	{
		*x-- = '0' + n % 10;
		n /= 10;
	}
	if (o)
		*x-- = '-';
	x++;
	return (ft_strdup(x));
}

char	*ft_itoa(int n)
{
	return (_ft_itoa(n, 0));
}
