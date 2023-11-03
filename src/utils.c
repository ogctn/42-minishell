/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:49:00 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/03 03:22:34 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	*ft_last(t_data *lst)
{
	t_data	*iter;

	if (!lst)
		return (NULL);
	iter = lst;
	while (iter->next)
		iter = iter->next;
	return (iter);
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

int	is_operate(char s)
{
	if (s == '<' || s == '>' || s == '|')
		return (1);
	return (0);
}

int	is_quote(char s)
{
	if (s == '\'' || s == '"')
		return (1);
	return (0);
}

int	in_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
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

void	list_add(char *str, t_data **total_line)
{
	t_data	*tmp;

	if (!(*total_line))
		(*total_line) = ft_create(str);
	else
	{
		tmp = ft_last(*total_line);
		tmp->next = ft_create(str);
	}
}
