/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 14:56:57 by asaijers      #+#    #+#                 */
/*   Updated: 2023/02/23 16:13:23 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	q(t_parser *p)
{
	return (p->b[p->c]);
}

char	*qq(t_parser *p)
{
	return (p->b + p->c);
}

int	ft_isquote(int c)
{
	return (c == '"' || c == '\'');
}

int	_isdelim(int c)
{
	return (ft_isquote(c) || ft_isspace(c) || c == '>' || c == '<' || c == '|');
}

void	str_tolower(char *s)
{
	while (*s)
	{
		*s = ft_tolower(*s);
		s++;
	}
}
