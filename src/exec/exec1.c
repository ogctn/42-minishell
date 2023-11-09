/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:17:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/09 17:47:28 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**data_to_double_arr(t_data *d)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_lstsize(d) + 1));
	ret[ft_lstsize(d)] = NULL;
	while (d)
	{
		ret[i++] = ft_strdup(d->content);
		d = d->next;
	}
	return (ret);
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_double_arr(t_env *env)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (env_size(env) + 1));
	ret[env_size(env)] = NULL;
	while (env)
	{
		ret[i++] = ft_strdup(env->content);
		env = env->next;
	}
	return (ret);
}

int	cd_err_is_file_or_permission(char *cmd_path)
{
	struct stat	sb;

	if (stat(cmd_path, &sb) == 0)
	{
		if (sb.st_mode & S_IFDIR)
			printf("minishell: cd: %s: Permission denied\n", cmd_path);
		else
			printf("minishell: cd: %s: Not a directory\n", cmd_path);
	}
	else
		printf("minishell: cd: %s: No such file or directory\n", cmd_path);
	return (1);	
}

int	exec_simple(t_data *d)
{
	char	**args;
	pid_t	pid;
	char	*cmd_path;

	if (is_buitin(d->content))
		return (exec_builtin(d));
	else
	{
		pid = fork();
		if (pid == 0)
		{
			args = data_to_double_arr(d);
			cmd_path = path_finder(args[0], d->env);
			if (execve(cmd_path, args, env_to_double_arr(d->env)) == -1)
 			{
				if (file_or_dir_exists(cmd_path, 2))
					return (cd_err_is_file_or_permission(cmd_path));
				exit (1);
			}
		}
		else
			wait(NULL);
		return (0);
	}
}

int	executer(t_data *data)
{
	int		pipe_count;
	//int		redir_count;
	//int		redir_type;

	pipe_count = 0;
	//count_char(read_line, '|', &pipe_count);
	if (pipe_count == 0)
			return (exec_simple(data));
	return (0);
}
