/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 11:33:26 by tmercier      #+#    #+#                 */
/*   Updated: 2023/02/28 17:20:16 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

char	*token_str(t_parser *p)
{
	char	c;
	char	*r;
	char	*b;
	char	*pv;

	c = q(p);
	if (!ft_isquote(c))
		return (0);
	r = 0;
	p->c++;
	b = ft_strchr(qq(p), c);
	if (!b)
		return (g_global.exitcode = 2, perror("missing quote"), NULL);
	pv = ft_strndup(qq(p), b - qq(p));
	if (c == '"')
	{
		r = _expand(p, pv);
		free(pv);
	}
	else
		r = pv;
	p->c = b - p->b + 1;
	return (r);
}

static char	*_trim(char *v)
{
	char	*a;
	char	*b;
	char	*r;

	a = v;
	while (ft_isspace(*a))
		a++;
	b = a + ft_strlen(a) - 1;
	while (b > a && ft_isspace(*b))
		b--;
	r = ft_strndup(a, b - a + 1);
	return (r);
}

int	wc(t_parser *p, int (*f)(int), int n)
{
	int	i;

	i = 0;
	if (n)
		while (p->b[p->c + i] && !f(p->b[p->c + i]))
			i++;
	else
		while (p->b[p->c + i] && f(p->b[p->c + i]))
			i++;
	return (i);
}

void	_token_id(t_parser *p, t_vector *b)
{
	char	*v;
	char	*w;
	char	*y;
	char	*z;
	int		n;

	n = wc(p, _isdelim, 1);
	z = ft_strndup(qq(p), n);
	w = _expand_fisrt(p, z);
	v = _expand(p, w);
	y = _trim(v);
	if (y)
		ft_vector_concat(b, y, ft_strlen(y));
	p->c += n;
	if (ft_isquote(q(p)) && ft_strlen(y) != ft_strlen(v))
	{
		ft_vector_push(b, " ");
	}
	free(z);
	free(v);
	free(w);
	free(y);
}

t_token	token_id(t_parser *p)
{
	t_vector	*b;
	char		*z;
	char		*v;

	b = ft_vector_create(sizeof(char));
	while (q(p))
	{
		if (ft_isquote(q(p)))
		{
			z = token_str(p);
			if (!z)
				return (ft_vector_destroy(b), tk(_TK_ERROR, 0));
			ft_vector_concat(b, z, ft_strlen(z));
			free(z);
		}
		else if (_isdelim(q(p)))
			break ;
		else
			_token_id(p, b);
	}
	ft_vector_push(b, &(char){0});
	v = ft_strdup(b->data);
	ft_vector_destroy(b);
	return (tk(TK_ID, v));
}
