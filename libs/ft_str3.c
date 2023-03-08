/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:11:01 by asaijers      #+#    #+#                 */
/*   Updated: 2022/10/27 21:18:11 by alfa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

static char	*_ft_strtrim(char const *s1, char const *set, const char *a,
		const char *b)
{
	size_t		l1;
	const char	*c;

	l1 = ft_strlen(s1);
	a = s1;
	b = s1 + l1;
	while (*a)
	{
		c = set;
		while (*c && *c != *a)
			c++;
		if (!*c)
			break ;
		a++;
	}
	while (b > a)
	{
		c = set;
		while (*c && *c != *b)
			c++;
		if (!*c && *b)
			break ;
		b--;
	}
	return (ft_substr(s1, a - s1, b + 1 - a));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	return (_ft_strtrim(s1, set, 0, 0));
}

static char	**alloc_split(const char *s, char c)
{
	int			i;
	const char	*b;

	if (!s)
		return (0);
	i = 0;
	b = s;
	while (*s)
	{
		b = s;
		while (*b && *b != c)
			b++;
		if (b != s)
		{
			i++;
			s = b;
		}
		while (*s && *s == c)
			s++;
	}
	return (ft_calloc(i + 1, sizeof(char *)));
}

static char	**free_split(char **a)
{
	char	**x;

	x = a;
	while (*x)
		free(*x++);
	free(a);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char		**a;
	char		**r;
	const char	*b;

	a = alloc_split(s, c);
	if (!a)
		return (0);
	r = a;
	while (*s)
	{
		b = s;
		while (*b && *b != c)
			b++;
		if (b != s)
		{
			*a = ft_substr(s, 0, b - s);
			if (!*a++)
				return (free_split(r));
			s = b;
		}
		while (*s && *s == c)
			s++;
	}
	return (r);
}
