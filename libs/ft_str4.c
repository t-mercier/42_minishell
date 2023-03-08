/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str4.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:06:16 by asaijers      #+#    #+#                 */
/*   Updated: 2022/10/27 21:18:11 by alfa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

size_t	ft_strlen(const char *s)
{
	const char	*a;

	a = s;
	while (*s)
		s++;
	return (s - a);
}

size_t	ft_strnlen(const char *s, size_t n)
{
	const char	*a;

	a = s;
	while (*s && n)
	{
		s++;
		n--;
	}
	return (s - a);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;

	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	len = min(len, ft_strlen(s + start));
	r = ft_malloc(len + 1);
	if (!r)
		return (0);
	ft_strlcpy(r, s + start, len + 1);
	return (r);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*r;
	const char	*a;
	char		*q;

	r = ft_malloc(ft_strlen(s) + 1);
	if (!r)
		return (0);
	q = r;
	a = s;
	while (*a)
	{
		*r++ = f(a - s, *a);
		a++;
	}
	*r = 0;
	return (q);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char	*a;

	a = s;
	while (*a)
	{
		f(a - s, a);
		a++;
	}
}
