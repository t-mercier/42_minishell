/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirout.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 16:55:42 by tmercier      #+#    #+#                 */
/*   Updated: 2023/02/08 17:46:47 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_close_ro(t_ro *ro, t_fd *fd)
{
	if (ro->is_append)
		fd->out = open(ro->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd->out = open(ro->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd->out < 0)
		exit_error("fd->out open", 1);
	return (fd->out);
}

int	process_redirout(t_cmd *c, t_fd *fd)
{
	size_t	i;
	t_ro	ro;

	i = 0;
	while (i < c->rout->len - 1)
	{
		ro = *(t_ro *)ft_vector_get(c->rout, i++);
		fd->out = open_close_ro(&ro, fd);
	}
	ro = *(t_ro *)ft_vector_get(c->rout, i);
	fd->out = open_close_ro(&ro, fd);
	return (fd->out);
}

void	process_delim(t_ri *ri, t_fd *fd)
{
	char	*line;
	int		pip[2];

	pipe(pip);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strncmp(line, ri->file, ft_strlen(ri->file)))
			break ;
		write(pip[1], line, ft_strlen(line));
	}
	fd->in = pip[0];
	close(pip[1]);
}

void	process_fdin(t_fd *fd, t_ri *ri)
{
	if (ri->is_delim)
		process_delim(ri, fd);
	else
	{
		fd->in = open(ri->file, O_RDONLY, 0644);
		if (fd->in < 0)
			exit_error("opening file", 1);
	}
}

int	process_redirin(t_cmd *c, t_fd *fd)
{
	size_t	i;
	t_ri	ri;

	i = 0;
	if (!c->rin->len)
		return (0);
	while (i < c->rin->len - 1)
	{
		ri = *(t_ri *)ft_vector_get(c->rin, i++);
		process_fdin(fd, &ri);
	}
	ri = *(t_ri *)ft_vector_get(c->rin, i);
	process_fdin(fd, &ri);
	return (fd->in);
}
