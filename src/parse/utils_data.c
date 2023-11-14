/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:45:46 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/14 19:46:52 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	list_add(char *str, t_data **total_line)
{
	t_data	*tmp;

	if (str && *str)
	{
		if ((*total_line))
		{
			tmp = ft_last(*total_line);
			tmp->next = ft_create(str);
		}
		else
			(*total_line) = ft_create(str);
	}
}

int	ft_lstsize(t_data *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_data	*ft_create(char *str)
{
	t_data	*new;

	new = ft_calloc(sizeof(t_data), 1);
	new->content = str;
	new->type = 0;
	new->next = NULL;
	return (new);
}

t_data	*ft_last(t_data *lst)
{
	while (lst)
	{
		if (lst->next)
			lst = lst->next;
		else
			return (lst);
	}
	return (NULL);
}
