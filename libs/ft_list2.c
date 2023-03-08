/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_list2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:10:30 by asaijers      #+#    #+#                 */
/*   Updated: 2022/10/12 12:26:34 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*a;
	t_list	*next;

	a = *lst;
	while (a)
	{
		next = a->next;
		ft_lstdelone(a, del);
		a = next;
	}
	*lst = 0;
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*prev;
	t_list	*l;
	t_list	*start;

	prev = 0;
	start = 0;
	while (lst)
	{
		l = ft_lstnew(f(lst->content));
		if (!l)
		{
			ft_lstclear(&prev, del);
			return (0);
		}
		if (!start)
			start = l;
		if (prev)
			prev->next = l;
		prev = l;
		lst = lst->next;
	}
	return (start);
}
