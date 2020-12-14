/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:44:35 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/04 14:05:42 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		my_lstsize(t_list *lst)
{
	int		size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		++size;
	}
	return (size);
}

static t_list	*my_lstnew(void *content)
{
	t_list	*new_list;

	new_list = (t_list*)malloc(sizeof(t_list));
	if (0 == new_list)
		return (0);
	new_list->content = content;
	new_list->next = 0;
	return (new_list);
}

static void		my_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	temp = *lst;
	while (temp)
	{
		temp2 = temp->next;
		(*del)(temp->content);
		free(temp);
		temp = temp2;
	}
	*lst = 0;
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*begin;
	int		lstsize;

	if (!lst)
		return (0);
	lstsize = my_lstsize(lst);
	new_list = my_lstnew((*f)(lst->content));
	if (!new_list)
		return (0);
	begin = new_list;
	lst = lst->next;
	while (--lstsize)
	{
		new_list->next = my_lstnew((*f)(lst->content));
		if (!new_list->next)
		{
			my_lstclear(&begin, (*del));
			return (0);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	return (begin);
}
