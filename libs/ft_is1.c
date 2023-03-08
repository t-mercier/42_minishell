/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:09:31 by asaijers      #+#    #+#                 */
/*   Updated: 2022/10/11 14:50:00 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_islower(int c)
{
	return ('a' <= c && c <= 'z');
}

int	ft_isupper(int c)
{
	return ('A' <= c && c <= 'Z');
}

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}
