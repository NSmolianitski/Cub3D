/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:23:27 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/03 14:50:57 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	new_list = (t_list*)malloc(sizeof(t_list));
	if (0 == new_list)
		return (0);
	new_list->content = content;
	new_list->next = 0;
	return (new_list);
}
