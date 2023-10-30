/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:09:59 by ogcetin           #+#    #+#             */
/*   Updated: 2023/01/28 20:31:24 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*i;

	tmp = 0;
	while (lst)
	{
		i = ft_lstnew((*f)(lst->content));
		if (i == 0)
			ft_lstclear(&i, (*del));
		else
			ft_lstadd_back(&tmp, i);
		lst = lst->next;
	}
	return (tmp);
}
