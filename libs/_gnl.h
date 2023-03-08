/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _gnl.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:34:10 by asaijers      #+#    #+#                 */
/*   Updated: 2023/03/02 13:44:45 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GNL_H
# define _GNL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct s_gnl
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	bl;
	ssize_t	dx;
	int		ofd;
	char	*line;
	size_t	odx;
	char	*a;
	int		nl;
	int		fd;
}			t_gnl;

void		*_gnl_memcpy(void *dst, void *src, size_t n);
size_t		_gnl_strlen(const char *s);
void		*_gnl_fake_realloc(void *p, size_t on, size_t n);
char		*get_next_line(int fd);

#endif