/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:04:22 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/13 22:56:31 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_swap(t_env *a, t_env *b, int *swap_flag)
{
	char	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
	*swap_flag = 1;
}

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

int	is_env_exist(t_env *env, char *content)
{
	int	len_to_equal;

	while (env)
	{
		if (ft_strchr(env->content, '='))
			len_to_equal = ft_strchr(env->content, '=') - env->content;
		else
			len_to_equal = ft_strlen(env->content);
		if (ft_strncmp(env->content, content, len_to_equal) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	update_env_content(t_env **env, char *new)
{
	int	len_to_equal;

	while (*env)
	{
		if (ft_strchr((*env)->content, '='))
			len_to_equal = ft_strchr((*env)->content, '=') - (*env)->content;
		else
			len_to_equal = ft_strlen((*env)->content);
		if (ft_strncmp((*env)->content, new, len_to_equal) == 0)
		{
			if (ft_strchr((*env)->content, '=') && !ft_strchr(new, '='))
				return ;
			free((*env)->content);
			(*env)->content = ft_strdup(new);
			return ;
		}
		*env = (*env)->next;
	}
}

void	add_to_env(t_env **env, char *content)
{
	if (is_env_exist(*env, content))
		update_env_content(env, content);
	else
		node_add_back(env, content);
}

int	is_valid_export_parameter(char *str)
{
	int	i;

	if (!str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return (0);
	}
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
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
