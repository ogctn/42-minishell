/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:49:12 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/16 18:50:18 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_there_oldpwd_in_env(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->content, "OLDPWD=", 7) == 0)
			return (1);
		env = env->next;
	}
	printf("minishell: cd: OLDPWD not set\n");
	return (0);
}

static int	is_there_home_in_env(t_env *env)
{
	if (!get_env_value(env, "HOME"))
	{
		printf("minishell: cd: HOME not set\n");
		return (0);
	}
	return (1);
}

int	are_valid_cd_params(t_data *d)
{
	if (d->next && d->next->type != 1)
	{
		if (!d->next->content)
			return (0);
		if (d->next->content[0] == '-')
		{
			if (!d->next->content[1])
				return (is_there_oldpwd_in_env(d->env));
			else if (d->next->content[1] == '-' && !d->next->content[2])
				return (is_there_home_in_env(d->env));
			else
			{
				printf("minishell: cd: -%c: invalid option\n\
cd: [tnoyan] No parameters supported in minishell\n", d->next->content[1]);
				printf("cd: usage: cd [dir]\n");
				return (0);
			}
		}
		return (1);
	}
	return (is_there_home_in_env(d->env));
}
