/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:34:33 by asaijers      #+#    #+#                 */
/*   Updated: 2022/11/30 18:09:01 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_gnl.h"

static char	*string_append_buf(char *str, char *buf, size_t bl)
{
	ssize_t	l1;
	size_t	l2;

	if (str)
		l1 = _gnl_strlen(str);
	else
		l1 = 0;
	l2 = bl;
	str = _gnl_fake_realloc(str, l1 + 1, l1 + l2 + 1);
	if (!str)
		return (0);
	_gnl_memcpy(str + l1, buf, l2);
	str[l1 + l2] = 0;
	return (str);
}

static void	find_nl(t_gnl *gnl)
{
	gnl->odx = gnl->dx;
	gnl->a = gnl->buf + gnl->dx;
	while (*gnl->a && *gnl->a != '\n')
		gnl->a++;
	gnl->nl = *gnl->a == '\n';
	if (gnl->nl)
		gnl->a++;
	gnl->dx = gnl->a - gnl->buf;
}

static void	reset(t_gnl *gnl, int fd)
{
	gnl->fd = fd;
	gnl->a = 0;
	gnl->line = 0;
	gnl->odx = 0;
	gnl->a = 0;
	gnl->nl = 0;
	if (gnl->ofd != gnl->fd)
	{
		gnl->dx = 0;
		gnl->bl = 0;
		gnl->ofd = gnl->fd;
	}
}

static char	*read_more(t_gnl *gnl)
{
	gnl->dx = 0;
	gnl->bl = read(gnl->fd, gnl->buf, BUFFER_SIZE);
	if (gnl->bl == -1)
	{
		gnl->bl = 0;
		gnl->dx = 0;
		if (gnl->line)
			free(gnl->line);
		return (0);
	}
	gnl->buf[gnl->bl] = 0;
	return ((char *)1);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;

	reset(&gnl, fd);
	while (1)
	{
		if (gnl.dx == gnl.bl)
		{
			if (!read_more(&gnl))
				return (0);
			if (!gnl.bl)
			{
				gnl.dx = 0;
				return (gnl.line);
			}
		}
		find_nl(&gnl);
		gnl.line = string_append_buf(gnl.line, gnl.buf + gnl.odx, gnl.dx
				- gnl.odx);
		if (!gnl.line)
			return (0);
		if (gnl.bl < BUFFER_SIZE || gnl.nl)
			break ;
	}
	return (gnl.line);
}
