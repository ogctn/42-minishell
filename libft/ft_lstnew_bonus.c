/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 04:23:32 by ogcetin           #+#    #+#             */
/*   Updated: 2023/01/28 20:13:17 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*element1;

	element1 = (t_list *)malloc(sizeof(t_list));
	if (!element1)
		return (0);
	element1 -> content = content;
	element1 -> next = 0;
	return (element1);
}
