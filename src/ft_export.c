/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:04:22 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/04 12:31:50 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env_swap(t_env *a, t_env *b, int *swap_flag)
{
    char	*tmp;

	tmp = ft_strdup(a->content);
	free(a->content);
	a->content = ft_strdup(b->content);
	free(b->content);
    b->content = ft_strdup(tmp);
	free(tmp);
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
            break; 
    }
}

t_env	*get_listed_env(t_env *env)
{
	t_env	*tmp;
	t_env	*ret;

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

	listed_env = get_listed_env(env);
	if (!listed_env)
		return ;
	while (listed_env)
	{
		if (ft_strchr(listed_env->content, '='))
			printf("declare -x \"%s\"\n", listed_env->content);
		listed_env = listed_env->next;
	}
}
int	is_env_exist(t_env *env, char *content)
{
	while (env)
	{
		if (!ft_strncmp(env->content, content, ft_strlen(content)))
			return (1);
		env = env->next;
	}
	return (0);
}
int	update_env_content(t_env *env, char *content)
{
	while (env)
	{
		if (ft_strncmp(env->content, content, ft_strlen(content)) == 0)
		{
			if (ft_strchr(env->content, '=') && !ft_strchr(content, '='))
				return (0);
			free(env->content);
			env->content = ft_strdup(content);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

int	add_to_env(t_data *d)
{

	if (!are_valid_params(d, "export"))
		return (1);
	if (is_env_exist(d->env, d->next->content))
		return (update_env_content(d->env, d->next->content));
	// else
	// 	return (add_to_env_list(d->env, d->next->content));
	 return (0);
}

int	ft_export(t_data *d)
{
	if (!d->next)
	{
		print_export(d->env);
		return (0);
	}
	else
		if (add_to_env(d))
			return (1);
	return (0);
}
