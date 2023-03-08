/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd_1.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 16:22:27 by asaijers      #+#    #+#                 */
/*   Updated: 2023/02/28 15:16:46 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir(t_parser *p, t_cmd *c, t_token t)
{
	t_token	nt;

	if (p->xt[t.type] != 1)
		return (2);
	nt = token(p);
	if (nt.type != TK_ID)
	{
		return (g_global.exitcode = 2, cmd_destroy(c), free(nt.val), 0);
	}
	if (t.type == TK_BT)
		ft_vector_push(c->rout, &(t_ro){nt.val, 0});
	else if (t.type == TK_LT)
		ft_vector_push(c->rin, &(t_ri){nt.val, 0});
	else if (t.type == TK_DBT)
		ft_vector_push(c->rout, &(t_ro){nt.val, 1});
	else if (t.type == TK_DLT)
		ft_vector_push(c->rin, &(t_ri){nt.val, 1});
	free(t.val);
	return (1);
}

int	_get_cmd(t_parser *p, t_cmd *c, t_token t)
{
	int	x;

	x = redir(p, c, t);
	if (!x)
		return (free(t.val), 0);
	else if (t.type == TK_ID && t.val)
		ft_vector_push(c->args, &t.val);
	else if (t.type == TK_PIPE)
	{
		free(t.val);
		if (!c->args->len)
			return (g_global.exitcode = 2, cmd_destroy(c), free(t.val), 0);
		c->next = get_cmd(p);
		if (!c->next)
			return (g_global.exitcode = 2, cmd_destroy(c), free(t.val), 0);
	}
	else if (x == 2)
		return (1);
	return (2);
}

t_cmd	*get_cmd(t_parser *p)
{
	t_token	t;
	t_cmd	*c;
	int		x;

	x = 1;
	c = cmd();
	while ((x) == 1)
		x = redir(p, c, (t = token(p)));
	if (!x)
		return (0);
	while (t.type != _TK_INVALID)
	{
		x = _get_cmd(p, c, t);
		if (x == 1)
			break ;
		else if (!x)
			return (0);
		t = token(p);
		if (t.type == _TK_ERROR)
			return (cmd_destroy(c), NULL);
	}
	if (!c->args->len)
		return (g_global.exitcode = 2, cmd_destroy(c), free(t.val), NULL);
	str_tolower(*(char **)ft_vector_get(c->args, 0));
	return (c);
}

t_cmdl	*get_cmdl(t_parser *p)
{
	t_cmdl	*cl;

	cl = malloc(sizeof(t_cmdl));
	cl->head = get_cmd(p);
	return (cl);
}
