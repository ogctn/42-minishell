/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:03:49 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/01 12:41:08 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	if (s2[i] == '\0')
		return (0);
	else
		return (-s2[i]);
}

int	is_buitin(char	*cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_data *data, char **env)
{
	if (ft_strcmp(data->content, "echo") == 0)	// -n -n -n -n -n , -nnnn, -n-n ->çalışmaz
		return (ft_echo(data));
	// else if (ft_strcmp(cmd, "cd") == 0)
	// 	return (ft_cd(data, env));
	// else if (ft_strcmp(cmd, "pwd") == 0)
	// 	return (ft_pwd(data, env));
	// else if (ft_strcmp(cmd, "export") == 0)
	// 	return (ft_export(data, env));
	// else if (ft_strcmp(cmd, "unset") == 0)	// path unset atınca komut çalışmasın (accsess bulamasın)
	// 	return (ft_unset(data, env));
	// else if (ft_strcmp(cmd, "env") == 0)
	// 	return (ft_env(data, env));
	// else if (ft_strcmp(cmd, "exit") == 0)
	// 	return (ft_exit(data));
	return (0);
}

