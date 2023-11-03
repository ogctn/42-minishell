/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:41:50 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/03 03:17:41 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_there_problem(char *content)
{
	int	i;

	if (!content[0] || (!ft_isalpha(content[0]) && content[0] != '_'))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", content);
		return (1);
	}
	i = 1;
	while (content[i])
	{
		if (!ft_isalnum(content[0]) && content[0] != '_')
		{
			printf("minishell: unset: `%s': not a valid identifier\n", content);
			return (1);
		}
		i++;
	}
	return (0);
}

int	are_valid_unset_params(t_data *d)
{
	if (!((d->next) && (d->next->content)))
		return (0);
	d = d->next;
	if (d->content[0] == '-')
	{
		if (!d->content[1])
		{
			printf("minishell: unset: `%s': \
not a valid identifier\n", d->content);
			return (1);
		}
		printf("minishell: unset: [tnoyan] there are no parameter option!\n");
		return (0);
	}
	while (d && !is_operate(d->content[0]))
	{
		if (is_there_problem(d->content))
			return (0);
		d = d->next;
	}
	return (1);
}

int	unset_one_argument(t_env **env, char *target)
{
	t_env	*tmp;
	t_env	*prev;
	char	*find;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		find = ft_strjoin_null(target, "=", NULL);
		if (ft_strncmp(tmp->content, find, ft_strlen(target) + 1))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->content);
			free(tmp);
			free(find);
			return (0);
		}
		free(find);
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	ft_unset(t_data *d)
{
	if (!are_valid_unset_params(d))
		return (1);
	d = d->next;
	while (d && !is_operate(d->content[0]))
	{
		if (unset_one_argument(&d->env, d->content))
			return (1);
		d = d->next;
	}
	return (0);
}
