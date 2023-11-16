/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:17:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/16 19:19:42 by sgundogd         ###   ########.fr       */
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
		}
		exit(1);
	}
	else
		wait(NULL);
	return (0);
}

void	redirect_and_execute(t_data **data)
{
	t_data	*tmp;

	tmp = *data;
	while (tmp && tmp->type != 1)
	{
		if (tmp->type == 2 || tmp->type == 3
			|| tmp->type == 5 || tmp->type == 4)
		{
			if (tmp->type == 2 || tmp->type == 3)
			{
				if (redir_in(data, tmp))
					return ;
			}
			else if (tmp->type == 4 || tmp->type == 5)
				redir_out(data, tmp);
			tmp = *data;
		}
		else
			tmp = tmp->next;
	}
	*((*data)->env->exit_code) = exec_simple(*data);
}

int	executer(t_data *data)
{
	int	default_fds[2];
	int	pipe_count;
	int	pipe_fd[2];
	int	pid;

	pipe_count = count_pipes(data);
	if (pipe_count > 0)
	{
		while (pipe_count > 0)
		{
			copy_default_fd(&default_fds[0], &default_fds[1]);
			if (pipe_count > 0)
				pipe(pipe_fd);
			pid = fork();
			if (pid == 0)
			{
				if (pipe_count > 0)
				{
					dup2(pipe_fd[1], STDOUT_FILENO);
					close(pipe_fd[0]);
					close(pipe_fd[1]);
				}
				redirect_and_execute(&data);
				exit(0);
			}
			else
			{
				if (pipe_count > 0)
				{
					dup2(pipe_fd[0], STDIN_FILENO);
					close(pipe_fd[0]);
					close(pipe_fd[1]);
				}
				else
					restore_defaults(default_fds);
				update_pipeline(&data);
			}
			wait(NULL);
			pipe_count--;
		}
	}
	copy_default_fd(&default_fds[0], &default_fds[1]);
	redirect_and_execute(&data);
	restore_defaults(default_fds);
	return (0);
}
