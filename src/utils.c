/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:49:00 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/01 11:05:21 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	new = malloc(sizeof(t_data));
	new->content = str;
	new->next = NULL;
	new->type = 0;
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
