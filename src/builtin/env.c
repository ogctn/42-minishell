/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:53:52 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/09 17:04:57 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_default_env(t_env **env_list, char **env)
{
	t_env	*new_env;
	t_env	*last_env;
	int		i;

	*env_list = NULL;
	last_env = NULL;
	i = -1;
	while (env[++i])
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			exit(127);
		new_env->content = strdup(env[i]);
		new_env->is_exported = 0;
		new_env->next = NULL;
		if (*env_list == NULL)
			*env_list = new_env;
		else
			last_env->next = new_env;
		last_env = new_env;
	}
}

char	*get_env_value(t_env *env, char *key)
{
	t_env	*tmp;
	int		len;

	tmp = env;
	key = ft_strjoin_null(key, "=", 0);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, key, ft_strlen(key)) == 0)
		{
			len = ft_strlen(key);
			return (free(key), tmp->content + len);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env_value(t_env *env, char *target, char *content)
{
	t_env	*tmp;

	tmp = env;
	target = ft_strjoin_null(target, "=", 0);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, target, ft_strlen(target)) == 0)
		{
			target = ft_strjoin_null(target, content, target);
			free(tmp->content);
			tmp->content = target;
			return ;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
		node_add_back(&env, ft_strjoin_null(target, content, target));
}
