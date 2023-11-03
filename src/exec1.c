/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:17:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/03 03:28:34 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
			execve(path_finder(args[0], d->env), \
					args, env_to_double_arr(d->env));
		}
		wait(NULL);
	}
	return (0);
}

int	executer(t_data *data)
{
	int		pipe_count;
	//int		redir_count;
	//int		redir_type;

	pipe_count = 0;
	//count_char(read_line, '|', &pipe_count);	// will be changed
	if (pipe_count == 0)
	{
		//if (redir_type == 0)
			return (exec_simple(data));
		// else if (redir_type == 1)
		// 	exec_redir_out(data);
		// else if (redir_type == 2)
		// 	exec_redir_in(data);
	}
	//else
		//if (exec_pipe(data))
	//		return (-1);
	return (0);
}
