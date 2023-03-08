/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 16:08:35 by asaijers      #+#    #+#                 */
/*   Updated: 2023/02/28 17:31:41 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	tk(int type, char *v)
{
	t_token	t;

	t.type = type;
	t.val = v;
	return (t);
}

const char	*token_name(int type)
{
	static char	*t[_TK_LEN];

	t[_TK_INVALID] = "INVALID";
	t[_TK_ERROR] = "ERROR";
	t[TK_ID] = "ID";
	t[TK_PIPE] = "PIPE";
	t[TK_BT] = "BT";
	t[TK_LT] = "LT";
	t[TK_DBT] = "DBT";
	t[TK_DLT] = "DLT";
	t[TK_DOLLAR] = "DOLLAR";
	t[TK_LP] = "LP";
	t[TK_RP] = "RP";
	t[TK_Q] = "Q";
	t[TK_SQ] = "SQ";
	t[TK_DQ] = "DQ";
	t[TK_STR] = "STR";
	return (t[type]);
}

t_token	_token(t_parser *p)
{
	int		*ct;
	t_token	t;

	ct = p->table;
	t.val = 0;
	t.type = _TK_INVALID;
	while (q(p) && ft_isspace(q(p)))
		p->c++;
	if (!ft_strncmp(qq(p), ">>", 2))
		return (p->c += 2, tk(TK_DBT, ft_strdup(">>")));
	else if (!ft_strncmp(qq(p), "<<", 2))
		return (p->c += 2, tk(TK_DLT, ft_strdup("<<")));
	else if (ct[(int)q(p)])
		return (tk(ct[(int)q(p)], ft_strndup(p->b + p->c++, 1)));
	else if (q(p))
		return (token_id(p));
	return (t);
}

t_token	token(t_parser *p)
{
	t_token	t;

	t = _token(p);
	return (t);
}
