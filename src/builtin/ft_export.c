/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:04:22 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/16 18:58:56 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sorter_function(t_env **env)
{
	int		swap_flag;
	t_env	*ptr;
	t_env	*cur;
	t_env	*prev;

	ptr = NULL;
	while (1)
	{
		swap_flag = 0;
		cur = *env;
		prev = NULL;
		while (cur->next != ptr)
		{
			if (strcmp(cur->content, cur->next->content) > 0)
				env_swap(cur, cur->next, &swap_flag);
			prev = cur;
			cur = cur->next;
		}
		ptr = cur;
		if (swap_flag == 0)
			break ;
	}
}

t_env	*get_listed_env(t_env *env)
{
	t_env	*tmp;
	t_env	*ret;

	if (!env)
		return (NULL);
	tmp = NULL;
	dup_env_list(&tmp, env);
	if (!tmp)
		return (NULL);
	ret = tmp;
	sorter_function(&tmp);
	return (ret);
}

void	print_export(t_env *env)
{
	t_env	*listed_env;
	char	*key;

	listed_env = get_listed_env(env);
	if (!listed_env)
		return ;
	while (listed_env)
	{
		if (ft_strchr(listed_env->content, '='))
		{
			key = ft_substr(listed_env->content, 0, \
			ft_strchr(listed_env->content, '=') - listed_env->content);
			printf("declare -x %s=\"%s\"\n", key, \
			ft_strchr(listed_env->content, '=') + 1);
		}
		else
		{
			key = ft_strdup(listed_env->content);
			printf("declare -x %s\n", key);
		}
		free(key);
		listed_env = listed_env->next;
	}
}

void	add_to_env(t_env **env, char *content)
{
	if (is_env_exist(*env, content))
		update_env_content(env, content);
	else
		node_add_back(env, content);
}

int	ft_export(t_data *d)
{
	if (!d->next || d->next->type == 1)
	{
		print_export(d->env);
		return (0);
	}
	d = d->next;
	if (d && d->content[0] == '-' && d->content[1] && d->type != 1)
	{
		printf("minishell: export: %s: [tnoyan] there are \
no parameter option!\n", d->content);
		d = d->next;
	}
	while (d && d->type != 1)
	{
		if (is_valid_export_parameter(d->content))
			add_to_env(&d->env, ft_strdup(d->content));
		d = d->next;
	}
	return (0);
}
