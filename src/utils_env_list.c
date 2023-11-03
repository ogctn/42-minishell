/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:13:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/03 03:23:17 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*node_get_last(t_env *env)
{
	t_env	*iter;

	iter = env;
	while (iter->next)
		iter = iter->next;
	return (iter);
}

t_env	*node_new(void *content)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (!element)
		return (NULL);
	element->content = content;
	element->is_exported = 0;
	element->next = NULL;
	return (element);
}

void	node_add_back(t_env **lst, char *content)
{
	t_env	*last;
	t_env	*new;

	new = node_new(content);
	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = node_get_last(*lst);
	last->next = new;
}

void	init_all_env_data_nodes(t_data **d, t_env *env_list)
{
	t_data	*iter;

	iter = *d;
	while (iter)
	{
		iter->env = env_list;
		iter = iter->next;
	}
}
