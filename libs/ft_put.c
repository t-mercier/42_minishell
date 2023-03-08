/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_put.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:10:46 by asaijers      #+#    #+#                 */
/*   Updated: 2022/10/27 21:18:11 by alfa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

static void	_ft_putnbr_fd(long long n, int fd, int o)
{
	char	_x[12];
	char	*x;

	x = _x;
	x += 11;
	*x-- = 0;
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
	ft_putstr_fd(x, fd);
}

void	ft_putnbr_fd(int _n, int fd)
{
	long long	n;

	n = _n;
	_ft_putnbr_fd(n, fd, 0);
}
