/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:53:52 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/03 03:08:45 by ogcetin          ###   ########.fr       */
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
