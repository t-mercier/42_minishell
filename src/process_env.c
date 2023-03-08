/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/18 17:23:04 by tmercier      #+#    #+#                 */
/*   Updated: 2023/02/28 13:11:31 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

t_vector	*build_env(char **envp)
{
	t_vector	*env;
	int			i;

	i = 0;
	env = ft_vector_create(sizeof(char *));
	if (envp[0] != NULL)
	{
		while (envp[i])
		{
			ft_vector_push(env, &(char *){ft_strdup(envp[i++])});
		}
	}
	else
	{
		ft_vector_push(env, ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin"));
	}
	return (env);
}
