/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:49:00 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/13 17:46:35 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

t_data	*ft_create(char *str)
{
	t_data	*new;

	new = ft_calloc(sizeof(t_data), 1);
	new->content = str;
	new->type = 0;
	new->next = NULL;
	return (new);
}

int is_operate(char s)
{
	if ( s == '<' || s == '>' ||s == '|')
		return(1);
	return(0);
}
int is_quote(char s)
{
	if ( s == '\'' || s == '"')
		return(1);
	return(0);
}
int in_quote(char *s)
{
	int i = 0;
	while (s[i])
	{
		if ( s[i] == '\'' || s[i] == '"' )
			return(1);
		i++;
	}
	return(0);
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
void list_add(char *str, t_data **total_line)
{
	t_data *tmp;
	if((*total_line))
	{
		tmp = ft_last(*total_line);
		tmp->next = ft_create(str);
	}
	else
		(*total_line) = ft_create(str);
}
