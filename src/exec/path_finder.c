/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:14:53 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/16 13:59:25 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**split_env_path(t_env *env)
{
	char	**ret;
	char	*tmp;
	int		i;

	i = 0;
	while (env)
	{
		tmp = ft_strnstr(env->content, "PATH=", 5);
		if (tmp)
		{
			free(tmp);
			tmp = ft_strdup(env->content + 5);
			ret = ft_split(tmp, ':');
			if (tmp)
				free(tmp);
			return (ret);
		}
		env = env->next;
	}
	return (NULL);
}

char	*ft_strjoin_null(char const *s1, char const *s2, void *freeable)
{
	size_t	len;
	char	*ret;

	if (!s1 || !s2)
		return (0);
	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	ret = (char *)ft_calloc(len, sizeof(char));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, ft_strlen(s1) + 1);
	ft_strlcat(ret, s2, len);
	if (freeable)
		free(freeable);
	return (ret);
}

void	free_2d(char **d)
{
	int	i;

	if (!d)
		return ;
	i = 0;
	while (d[i])
		free(d[i++]);
	free(d);
}

int	is_there_a_slash(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i++] == '/')
			return (1);
	}
	return (0);
}

// char	*path_finder(char *full_cmd, t_env *env)
// {
// 	t_path	path;
// 	int		i;

// 	if (is_there_a_slash(full_cmd))
// 		return (full_cmd);
// 	path.sp_env = split_env_path(env);
// 	path.sp_cmd = ft_split(full_cmd, ' ');
// 	i = -1;
// 	while (path.sp_env[++i])
// 	{
// 		path.full_path = ft_strjoin_null(path.sp_env[i], "/", NULL);
// 		path.full_path = "\"
// 			ft_strjoin_null(path.full_path, path.sp_cmd[0], path.full_path);
// 		if (access(path.full_path, F_OK) == 0)
// 		{
// 			free_2d(path.sp_cmd);
// 			free_2d(path.sp_env);
// 			return (path.full_path);
// 		}
// 		free(path.full_path);
// 	}
// 	free_2d(path.sp_cmd);
// 	free_2d(path.sp_env);
// 	return (NULL);
// }

char	*path_finder(char *full_cmd, t_env *env)
{
	t_path	p;
	int		i;

	p.sp_env = split_env_path(env);
	i = -1;
	while (p.sp_env[++i])
	{
		p.full_path = ft_strjoin_null(p.sp_env[i], "/", NULL);
		p.full_path = \
			ft_strjoin_null(p.full_path, full_cmd, p.full_path);
		if (access(p.full_path, F_OK) == 0)
		{
			free_2d(p.sp_env);
			return (p.full_path);
		}
		if (p.full_path)
			free(p.full_path);
	}
	free_2d(p.sp_env);
	return (NULL);
}
