/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/23 16:13:50 by tmercier      #+#    #+#                 */
/*   Updated: 2023/02/20 16:28:48 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_vector	*path_vector(t_vector *v, char *d, char *cmd)
{
	ft_vec_concat_str(v, d);
	ft_vec_concat_str(v, "/");
	ft_vec_concat_str(v, cmd);
	return (v);
}

t_path	*path_construct(DIR *curr, t_path *p)
{
	struct stat	buffer;

	p->v_path = path_vector(p->v_path, p->dir, p->cmd);
	p->path = ft_strdup((char *)p->v_path->data);
	if (stat(p->path, &buffer) != 0)
		exit_error("stat", 2);
	closedir(curr);
	ft_vector_destroy(p->v_path);
	return (p);
}

t_path	*path_dir(t_path *p, DIR *curr, struct dirent *s_dir)
{
	while (s_dir)
	{
		if (ft_strcmp(s_dir->d_name, p->cmd) == 0)
			return (path_construct(curr, p));
		s_dir = readdir(curr);
	}
	closedir(curr);
	return (p);
}
