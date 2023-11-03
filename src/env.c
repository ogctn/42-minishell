/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:53:52 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/03 14:34:08 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
char *get_env_value(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, key, ft_strlen(key) + 1) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int		set_env_value(t_env *env, char *target, char *content)
{
	// t_env	*tmp;
	// t_env	*prev;

	// content = ft_strjoin_null("=", content, content);
	// tmp = data->env;
	// prev = NULL;
	// while (tmp)
	// {
	// 	if (!ft_strncmp(tmp->content, to_find, ft_strlen(target) + 1))
	// 	{
	// 		if (prev)
	// 			prev->next = tmp->next;
	// 		else
	// 			data->env = data->env->next;
	// 		free(to_find);
	// 		init_env_all_data_nodes(&data, data->env);
	// 		return (0);
	// 	}
	// 	prev = tmp;
	// 	tmp = tmp->next;
	// }
	// free(to_find);
	return (1);
}