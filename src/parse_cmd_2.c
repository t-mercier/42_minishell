/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd_2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 16:25:51 by asaijers      #+#    #+#                 */
/*   Updated: 2023/02/28 15:02:11 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*cmd(void)
{
	t_cmd	*c;

	c = malloc(sizeof(t_cmd));
	c->args = ft_vector_create(sizeof(char *));
	c->next = 0;
	c->rin = ft_vector_create(sizeof(t_ri));
	c->rout = ft_vector_create(sizeof(t_ro));
	return (c);
}

void	cmd_destroy(t_cmd *c)
{
	size_t	i;

	if (!c)
		return ;
	cmd_destroy(c->next);
	i = 0;
	while (i < c->rin->len)
		free(*(char **)ft_vector_get(c->rin, i++));
	i = 0;
	while (i < c->rout->len)
		free(*(char **)ft_vector_get(c->rout, i++));
	i = 0;
	while (i < c->args->len)
		free(*(char **)ft_vector_get(c->args, i++));
	ft_vector_destroy(c->rin);
	ft_vector_destroy(c->rout);
	ft_vector_destroy(c->args);
	free(c);
}

// void	cmdl_print(t_cmdl *cl)
// {
// 	t_cmd	*c;
// 	int		i;
// 	t_ri	ri;
// 	t_ro	ro;

// 	c = cl->head;
// 	while (c)
// 	{
// 		printf("%zu. ", c->args->len);
// 		for (int i = 0; i < c->args->len; i++)
// 			printf("'%s' ", *(char **)ft_vector_get(c->args, i));
// 		printf(".\n");
// 		i = 0;
// 		printf("rin: ");
// 		while (i < c->rin->len)
// 		{
// 			ri = *(t_ri *)ft_vector_get(c->rin, i++);
// 			printf("%d.%s ", ri.is_delim, ri.file);
// 		}
// 		printf("\n");
// 		i = 0;
// 		printf("rout: ");
// 		while (i < c->rout->len)
// 		{
// 			ro = *(t_ro *)ft_vector_get(c->rout, i++);
// 			printf("%d.%s ", ro.is_append, ri.file);
// 		}
// 		printf("\n");
// 		c = c->next;
// 	}
// 	printf("\n");
// }
