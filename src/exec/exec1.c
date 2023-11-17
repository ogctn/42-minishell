/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:17:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/17 10:27:49 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	get_reason(char *path)
{
	struct stat	buffer;

	dup2(2, STDOUT_FILENO);
	if (access(path, F_OK) != 0)
	{
		if (!is_there_a_slash(path))
			return (printf("minishell: %s: command not found\n", path), 127);
		else if (is_there_a_slash(path))
			return (printf("minishell: %s: No such file or directory\n",
					path), 1);
		return (1);
	}
	if (stat(path, &buffer) == 0)
	{
		if (buffer.st_mode & S_IFDIR)
			return (printf("minishell: %s: is a directory\n", path), 1);
		else if (!(buffer.st_mode & S_IXUSR))
			return (printf("minishell: cd: %s: Permission denied\n", path), 1);
		else
			return (1);
	}
	else
		return (printf("minishell: cd: %s: No such file or directory\n", path)
			, 1);
}

int	exec_simple(t_data *d)
{
	pid_t	pid;
	int		status;

	if (d->type == 1)
		return (1);
	if (is_builtin(d->content))
		return (exec_builtin(d));
	pid = fork();
	if (pid == 0)
		child_part(d);
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (0);
}

void	redirect_and_execute(t_data **data, int default_fds[2])
{
	t_data	*tmp;
	int		a;

	tmp = *data;
	while (tmp && tmp->type != 1)
	{
		if (tmp->type > 1)
		{
			if (tmp->type == 2 || tmp->type == 3)
				a = redir_in(data, tmp, default_fds);
			else if (tmp->type == 4 || tmp->type == 5)
				a = redir_out(data, tmp);
			*tmp->env->exit_code = a;
			if (a)
				return ;
			tmp = *data;
		}
		else
			tmp = tmp->next;
	}
	if (*data)
		*((*data)->env->exit_code) = exec_simple(*data);
}

int	executer(t_data *data)
{
	t_norm_exec	a;

	a.i = 0;
	copy_default_fd(&a.default_fds[0], &a.default_fds[1]);
	a.pipe_count = count_pipes(data);
	while (a.pipe_count > 0)
	{
		pipe(a.pipe_fd);
		a.pid = fork();
		if (a.pid == 0)
			sub_exec(data, a.i, a.pipe_fd, a.default_fds);
		else
			wait(NULL);
		if (data->type != 1)
			update_pipeline(&data);
		else
			data = data->next;
		a.pipe_count--;
		a.i++;
	}
	sub_exec2(data, a.pipe_fd, a.default_fds);
	return (0);
}
