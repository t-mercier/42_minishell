/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_exp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 16:14:35 by asaijers      #+#    #+#                 */
/*   Updated: 2023/03/06 11:29:30 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*_strfchr(char *s, int (*f)(int), int n)
{
	if (n)
		while (*s && !f(*s))
			s++;
	else
		while (*s && f(*s))
			s++;
	return (s);
}

char	*_expand_env(t_parser *p, char *a, t_vector *r)
{
	char	*b;
	char	*k;
	char	*ec;
	char	*v;

	a++;
	if (*a == '?')
	{
		ec = ft_itoa(g_global.exitcode);
		ft_vector_concat(r, ec, ft_strlen(ec));
		return (++a);
	}
	if (!*a)
		return (ft_vector_push(r, "$"), a);
	if (!ft_isalpha(*a) && *a != '_')
		return (++a);
	b = _strfchr(a, isenv, 0);
	k = ft_strndup(a, b - a);
	v = _getenv(p->env, k);
	free(k);
	if (v)
		ft_vector_concat(r, v, ft_strlen(v));
	return (b);
}

char	*_expand(t_parser *p, char *a)
{
	t_vector	*r;
	char		*b;
	char		*s;

	r = ft_vector_create(sizeof(char));
	while (*a)
	{
		if (*a == '$')
		{
			(a = _expand_env(p, a, r));
			if (!a)
				return (ft_vector_destroy(r), NULL);
		}
		else
		{
			b = ft_strchr(a, '$');
			if (!b)
				b = ft_strchr(a, 0);
			ft_vector_concat(r, a, b - a);
			a = b;
		}
	}
	return ((s = ft_strndup(r->data, r->len)), ft_vector_destroy(r), s);
}

char	*_expand_fisrt(t_parser *p, char *a)
{
	t_vector	*r;
	char		*home;
	char		*s;

	r = ft_vector_create(sizeof(char));
	if (*a == '~')
	{
		a++;
		home = _getenv(p->env, "HOME");
		ft_vector_concat(r, home, ft_strlen(home));
	}
	while (*a)
		ft_vector_push(r, a++);
	s = ft_strndup(r->data, r->len);
	ft_vector_destroy(r);
	return (s);
}

t_cmdl	*parse(char *k, t_vector *env)
{
	t_parser	p;
	int			*ct;
	t_cmdl		*cl;

	if (!k)
		return (0);
	p = (t_parser){0};
	p.b = k;
	p.l = ft_strlen(k);
	p.env = env;
	ct = p.table;
	ct['|'] = TK_PIPE;
	ct['>'] = TK_BT;
	ct['<'] = TK_LT;
	p.xt[TK_BT] = 1;
	p.xt[TK_LT] = 1;
	p.xt[TK_DLT] = 1;
	p.xt[TK_DBT] = 1;
	cl = get_cmdl(&p);
	return (cl);
}
