/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:17:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/09 23:44:46 by ogcetin          ###   ########.fr       */
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
	while (d && !(d->content[0] == '|' && d->content[1]))
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

int	get_reason(char *path)
{
	struct stat	buffer;

	if (access(path, F_OK) != 0)
	{
		if (!is_there_a_slash(path))
			printf("minishell: %s: command not found\n", path);
		else if (is_there_a_slash(path))
			printf("minishell: %s: No such file or directory\n", path);
	}
	else
	{
		if (stat(path, &buffer) == 0)
		{
			if (buffer.st_mode & S_IFDIR)
				printf("minishell: %s: is a directory\n", path);
			else if (!(buffer.st_mode & S_IXUSR))
				printf("minishell: cd: %s: Permission denied\n", path);
			else
				return (0);
		}
		else
			printf("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}

// int	exec_simple(t_data *d)
// {
// 	char	**args;
// 	pid_t	pid;
// 	char	*cmd_path;

// 	if (is_buitin(d->content))
// 		return (exec_builtin(d));
// 	else
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			args = data_to_double_arr(d);
// 			cmd_path = path_finder(args[0], d->env);
// 			if (execve(cmd_path, args, env_to_double_arr(d->env)) == -1)
//  			{
// 				if (file_or_dir_exists(cmd_path, 2))
// 					return (cd_err_is_file_or_permission(cmd_path));
// 				exit (1);
// 			}
// 		}
// 		else
// 			wait(NULL);
// 		return (0);
// 	}
// }

int	exec_simple(t_data *d)
{
	char	**args;
	char	*cmd_path;
	pid_t	pid;

	if (is_buitin(d->content))
		return (exec_builtin(d));
	else
	{
		pid = fork();
		if (pid == 0)
		{
			args = data_to_double_arr(d);
			cmd_path = d->content;
			if (execve(cmd_path, args, env_to_double_arr(d->env)) == -1)
			{
				cmd_path = path_finder(args[0], d->env);
				if (cmd_path)
				{
					if (execve(cmd_path, args, env_to_double_arr(d->env)) == -1)
						get_reason(cmd_path);
				}
				else
					get_reason(cmd_path);
				exit(1);
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
