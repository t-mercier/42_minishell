/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   orun2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 13:21:53 by asaijers      #+#    #+#                 */
/*   Updated: 2023/02/28 17:27:34 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stddef.h>
#include <sys/fcntl.h>

void	e_rout(t_cmdl *cl, t_cmd *c, t_ff *f)
{
	size_t	i;
	t_ro	*ro;
	int		flag;

	(void)cl;
	if (!c->rout->len)
		return ;
	i = 0;
	while (i < c->rout->len)
	{
		ro = (t_ro *)ft_vector_get(c->rout, i++);
		if (ro->is_append)
			flag = O_APPEND;
		else
			flag = O_TRUNC;
		close(f->std[1]);
		f->std[1] = open(ro->file, O_WRONLY | O_CREAT | flag, 0644);
	}
}

void	e_rin_delim(t_ff *f, t_ri ri)
{
	char	*line;
	int		ipip[2];

	pipe(ipip);
	line = get_next_line(f->m[0]);
	while (line)
	{
		if (!ft_strncmp(line, ri.file, ft_strlen(ri.file)))
			break ;
		write(ipip[1], line, ft_strlen(line));
		line = get_next_line(f->m[0]);
	}
	f->std[0] = ipip[0];
	close(ipip[1]);
}

void	e_rin(t_cmdl *cl, t_cmd *c, t_ff *f)
{
	size_t	i;
	t_ri	ri;
	int		fd;

	(void)cl;
	if (!c->rin->len)
		return ;
	i = 0;
	while (i < c->rin->len)
	{
		ri = *(t_ri *)ft_vector_get(c->rin, i);
		close(f->std[0]);
		if (ri.is_delim)
			e_rin_delim(f, ri);
		else
		{
			fd = open(ri.file, O_RDONLY, 0644);
			if (fd < 0)
				exit_error("rin open", 1);
			f->std[0] = fd;
		}
		i++;
	}
}

void	e_pipe(t_cmdl *cl, t_cmd *c, t_ff *f)
{
	if (!c->next)
	{
		f->std[0] = f->ppip[0];
		close(f->ppip[1]);
	}
	else if (c == cl->head)
	{
		f->std[1] = f->pip[1];
		close(f->pip[0]);
	}
	else
	{
		f->std[0] = f->ppip[0];
		f->std[1] = f->pip[1];
		close(f->ppip[1]);
		close(f->pip[0]);
	}
}
