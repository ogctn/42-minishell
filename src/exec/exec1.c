/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:17:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/14 16:31:00 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**data_to_double_arr(t_data *d)
{
	char	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(sizeof(char *), (ft_lstsize(d) + 1));
	ret[ft_lstsize(d)] = NULL;
	while (d && d->type != 1)
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
	ret = ft_calloc(sizeof(char *), (env_size(env) + 1));
	ret[env_size(env)] = NULL;
	while (env)
	{
		ret[i++] = ft_strdup(env->content);
		env = env->next;
	}
	return (ret);
}

void	get_reason(char *path)
{
	struct stat	buffer;

	if (access(path, F_OK) != 0)
	{
		if (!is_there_a_slash(path))
			printf("minishell: %s: command not found\n", path);
		else if (is_there_a_slash(path))
			printf("minishell: %s: No such file or directory\n", path);
		return ;
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
				return ;
		}
		else
			printf("minishell: cd: %s: No such file or directory\n", path);
	}
}

int	exec_simple(t_data *d)
{
	char	**args;
	char	*cmd_path;
	pid_t	pid;

	if (is_builtin(d->content))
		return (exec_builtin(d));
	pid = fork();
	if (pid == 0)
	{
		args = data_to_double_arr(d);
		cmd_path = path_finder(d->content, d->env);
		if (execve(cmd_path, args, env_to_double_arr(d->env)) == -1)
		{
			if (access(d->content, F_OK) == 0)
			{
				cmd_path = d->content;
				if (execve(cmd_path, args, env_to_double_arr(d->env)) == -1)
					get_reason(d->content);
			}
			else
				get_reason(d->content);
			exit(1);
		}
	}
	else
		wait(NULL);
	return (0);
}

void	update_pipeline(t_data **d)
{
	t_data	*tmp;

	tmp = *d;
	while (tmp && tmp->type != 1)
		tmp = tmp->next;
	if (tmp)
	{
		tmp = tmp->next;
		while (*d && *d != tmp && (*d)->type != 1)
			*d = (*d)->next;
		*d = (*d)->next;
	}
}
void	init_default_fd(int *default_in, int *default_out)
{
	*default_in = dup(STDIN_FILENO);
	*default_out = dup(STDOUT_FILENO);
}

void	restore_defaults(int default_fds[2])
{
	dup2(default_fds[0], STDIN_FILENO);
	dup2(default_fds[1], STDOUT_FILENO);
	close(default_fds[0]);
	close(default_fds[1]);
}
void	redirect_and_execute(t_data **data, int *default_fds)
{
	redir_out(data);
	redir_in(data);
	*((*data)->env->exit_code) = exec_simple(*data);
}
int	executer(t_data *data)
{
	int	default_fds[2];
	
	//while start
	//fork gelse
	init_default_fd(&default_fds[0], &default_fds[1]);
	redirect_and_execute(&data, default_fds); // if *(data->env->exit_code) kısmını sildim README->NOTE(1)
	restore_defaults(default_fds);
	update_pipeline(&data);
	//while end
	return (0);
}
