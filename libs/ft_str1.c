/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:06:52 by asaijers      #+#    #+#                 */
/*   Updated: 2023/03/02 13:44:23 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	ll;
	size_t	bl;
	long	i;

	ll = ft_strlen(little);
	bl = ft_strlen(big);
	if (!ll)
		return (big);
	if (len > bl)
		len = bl;
	if (!little || bl < ll)
		return (0);
	i = 0;
	while (i <= (long)(len - ll))
	{
		if (*big == *little && !ft_strncmp(big, little, ll))
			return (big);
		big++;
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	char	*a;

	a = (char *)s;
	while (*a)
	{
		if (*a == (char)c)
			return (a);
		a++;
	}
	if (!(char)c)
		return (a);
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*a;

	a = (char *)s;
	a += ft_strlen(s);
	while (a >= s)
	{
		if (*a == (char)c)
			return (a);
		a--;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	while (n && *s1 && (*s2 == *s1))
	{
		s1++;
		s2++;
		n--;
	}
	if (!n)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	ft_strcmp(char const *s1, char const *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
