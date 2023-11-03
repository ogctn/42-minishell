/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:41:50 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/04 02:29:45 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_there_problem(char *content, char *cmd)
{
	int	i;

	if (!content[0] || (!ft_isalpha(content[0]) && content[0] != '_'))
	{
		printf("minishell: %s: `%s': not a valid identifier\n", cmd, content);
		return (1);
	}
	i = 1;
	while (content[i])
	{
		if (!ft_isalnum(content[0]) && content[0] != '_')
		{
			printf("minishell: %s: `%s': not a valid identifier\n", cmd, content);
			return (1);
		}
		i++;
	}
	return (0);
}

int	are_valid_params(t_data *d, char *cmd)
{
	if (!((d->next) && (d->next->content)))
		return (0);
	d = d->next;
	if (d->content[0] == '-')
	{
		if (!d->content[1])
		{
			printf("minishell: %s: `%s': \
not a valid identifier\n", cmd, d->content);
			return (1);
		}
		printf("minishell: %s: [tnoyan] there are \
no parameter option!\n", cmd);
		return (0);
	}
	while (d && !is_operate(d->content[0]))
	{
		if (is_there_problem(d->content, cmd))
			return (0);
		d = d->next;
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
			init_env_all_data_nodes(&data, data->env);
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
	if (!are_valid_params(d, "unset"))
		return (1);
	d = d->next;
	while (d && !is_operate(d->content[0]))
	{
		if (unset_single_env(d, d->content))
			return (1);
		d = d->next;
	}
	return (0);
}
