/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:03:00 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/03 14:33:33 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	while (env)
	{
		if (ft_strncmp(env->content, "HOME=", 5) == 0)
			return (1);
		env = env->next;
	}
	printf("minishell: cd: HOME not set\n");
	return (0);
}


int	are_valid_cd_params(t_data *d)
{
	if (d->next)
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
				return (1);
			}
		}
	}
	return (0);
}

static char	*goo(t_data *d)
{
	char	*path;

	if (d->next)
	{
		if (d->next->content[0] == '-')
		{
			if (d->next->content[1] == '-' && !d->next->content[2])
				path = get_env_value(d->env, "HOME");
			else
				path = get_env_value(d->env, "OLDPWD");
		}
		else
			path = d->next->content;
	}
	else
	{
		if (!is_there_home_in_env(d->env))
			return (NULL);
		path = get_env_value(d->env, "HOME");
	}
	return (path);
}

int	ft_cd(t_data *d)
{
	char	*path;
	char	*tmp;
	int		ret;

	if (!are_valid_cd_params(d))
		return (1);
	path = goo(d);
	if (!path)
		return (1);
	tmp = getcwd(NULL, 0);
	ret = chdir(path);
	if (ret == -1)
	{
		printf("minishell: Error at cd: %s\n", path);
		return (free(tmp), 1);
	}
	//set_env_value(d->env, "OLDPWD", tmp);
	//tmp = getcwd(NULL, 0);
	//set_env_value(d->env, "PWD", tmp);
	//free(tmp);
	return (0);
}
