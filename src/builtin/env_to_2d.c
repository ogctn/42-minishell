/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:16:39 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/17 10:30:01 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**env_to_double_arr(t_env *env)
{
	char	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(sizeof(char *), (env_size(env) + 1));
	ret[env_size(env)] = NULL;
	while (env)
	{
		ret[i++] = ft_strdup(env->content);
		env = env->next;
	}
	return (ret);
}

void	print_norm(char *content, char **key)
{
	if (ft_strchr(content, '='))
	{
		*key = ft_substr(content, 0, ft_strchr(content, '=') - content);
		printf("declare -x %s=\"%s\"\n", *key, ft_strchr(content, '=') + 1);
	}
	else
	{
		*key = ft_strdup(content);
		printf("declare -x %s\n", *key);
	}
}
