/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:03:00 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/17 10:31:36 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*arg_special_chars(t_data *d)
{
	char	*path;

	if (d->next && d->next->type != 1)
	{
		if (d->next->content[0] == '-')
		{
			if (!d->next->content[1])
			{
				path = get_env_value(d->env, "OLDPWD");
				printf("%s\n", path);
			}
			if (d->next->content[1] == '-' && !d->next->content[2])
				path = get_env_value(d->env, "HOME");
		}
		else
			path = d->next->content;
	}
	else if (!d->next || d->next->type == 1)
		path = get_env_value(d->env, "HOME");
	else
		path = NULL;
	return (path);
}

int	cd_is_valid_dir_and_permission(char *str)
{
	struct stat	buff;
	char		*full_path;

	if (access(str, F_OK) != 0)
	{
		full_path = NULL;
		full_path = getcwd(full_path, 0);
		full_path = ft_strjoin_null(full_path, "/", full_path);
		full_path = ft_strjoin_null(full_path, str, full_path);
	}
	else
		full_path = ft_strdup(str);
	if (stat(full_path, &buff) == 0)
	{
		if ((buff.st_mode & S_IFDIR))
		{
			if (!(buff.st_mode & S_IXUSR))
				return (printf("cd: permission denied: %s\n", full_path), \
						free(full_path), 0);
			else
				return (free(full_path), 1);
		}
		return (printf("cd: not a directory: %s\n", str), free(full_path), 0);
	}
	return (perror("minishell: cd"), free(full_path), 0);
}

int	ft_cd(t_data *d)
{
	char	*path;
	char	*tmp;

	path = arg_special_chars(d);
	if (!are_valid_cd_params(d) || !path)
		return (1);
	tmp = getcwd(NULL, 0);
	if (!cd_is_valid_dir_and_permission(path))
		return (free(tmp), 1);
	if (chdir(path) == -1)
	{
		perror("minishell:");
		return (free(tmp), 1);
	}
	if (get_env_value(d->env, "OLDPWD"))
		set_env_value(d->env, "OLDPWD", tmp);
	free(tmp);
	tmp = getcwd(NULL, 0);
	set_env_value(d->env, "PWD", tmp);
	free(tmp);
	return (0);
}
