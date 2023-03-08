/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/23 16:13:50 by tmercier      #+#    #+#                 */
/*   Updated: 2023/03/02 15:06:46 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_path	*get_cmd_path(t_path *p)
{
	DIR				*curr;
	struct dirent	*s_dir;
	int				i;

	i = 0;
	while (p->tab[i])
	{
		curr = opendir(p->tab[i]);
		if (!curr)
		{
			i++;
			continue ;
		}
		s_dir = readdir(curr);
		p->dir = p->tab[i];
		p = path_dir(p, curr, s_dir);
		i++;
	}
	return (p);
}

static char	**get_dir(t_cmdl *cl)
{
	char	*path;
	char	**dir;

	path = _getenv(cl->env, "PATH");
	if (!path)
		path = ".";
	while (*path)
	{
		if (ft_strnstr(path, "=", ft_strlen(path)) == 0)
			break ;
		path++;
	}
	dir = ft_split(path, ':');
	return (dir);
}

char	*build_path(t_cmdl *cl, t_cmd *cmd)
{
	t_path	p;

	p = (t_path){};
	p.tab = get_dir(cl);
	p.cmd = *(char **)cmd->args->data;
	p.v_path = ft_vector_create(sizeof(char));
	p = *get_cmd_path(&p);
	return (p.path);
}

char	*process_path(t_cmdl *cl, t_cmd *c)
{
	char		*path;
	struct stat	st;
	char		*a;

	a = *(char **)ft_vector_get(c->args, 0);
	if (!ft_strcmp(a, "."))
		exit_error("cmd path is .", 2);
	stat(*(char **)ft_vector_get(c->args, 0), &st);
	if (!ft_strcmp(a, ".."))
		exit_error("cmd path is ..", 127);
	if (S_ISDIR(st.st_mode))
		exit_error("cmd path is dir", 126);
	path = build_path(cl, c);
	if (!ft_strncmp(a, "./", 2) || !ft_strncmp(a, "/", 1))
		path = *(char **)c->args->data;
	if (!path)
		exit_error("command not found", 127);
	return (path);
}
