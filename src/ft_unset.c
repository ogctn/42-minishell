/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:41:50 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/06 04:32:02 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_valid_unset_parameter(char *content)
{
	int	i;

	if (!content[0] || (!ft_isalpha(content[0]) && content[0] != '_'))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", content);
		return (0);
	}
	i = 1;
	while (content[i])
	{
		if (!ft_isalnum(content[i]) && content[i] != '_')
		{
			printf("minishell: unset: `%s': not a valid identifier\n", content);
			return (0);
		}
		i++;
	}
	return (1);
}

int	unset_single_env(t_data *data, char *target)
{
	t_env	*tmp;
	t_env	*prev;
	char	*to_find;

	to_find = ft_strjoin_null(target, "=", NULL);
	tmp = data->env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, to_find, ft_strlen(target) + 1))
		{
			if (prev)
				prev->next = tmp->next;
			else
				data->env = data->env->next;
			free(to_find);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	free(to_find);
	return (1);
}

int	ft_unset(t_data *d)
{
	d = d->next;
	if (d && d->content[0] == '-' && d->content[1])
	{
		printf("minishell: unset: %s: [tnoyan] there are \
no parameter option!\n", d->content);
		d = d->next;
	}
	while (d && !(is_operate(d->content[0]) && !d->content[1]))
	{
		if (is_valid_unset_parameter(d->content))
			unset_single_env(d, d->content);
		d = d->next;
	}
	return (0);
}
