/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_list1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:10:15 by asaijers      #+#    #+#                 */
/*   Updated: 2022/10/19 14:18:53 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*a;

	a = ft_malloc(sizeof(t_list));
	if (!a)
		return (0);
	a->content = content;
	a->next = 0;
	return (a);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize(t_list *lst)
{
	int	n;

	n = 0;
	while (lst)
	{
		lst = lst->next;
		n++;
	}
	return (n);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
