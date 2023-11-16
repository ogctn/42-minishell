/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:17:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/16 22:58:49 by sgundogd         ###   ########.fr       */
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
	char	**args;
	char	*cmd_path;
	pid_t	pid;
	int		status;

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
					exit(get_reason(d->content));
			}
			else
				exit(get_reason(d->content));
		}
		exit(1);
	}
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

	tmp = *data;
	while (tmp && tmp->type != 1)
	{
		if (tmp->type == 2 || tmp->type == 3
			|| tmp->type == 5 || tmp->type == 4)
		{
			if ((tmp->type == 2 || tmp->type == 3)
				&& redir_in(data, tmp, default_fds))
				return ;
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
	int	i;

	i = 0;
	copy_default_fd(&default_fds[0], &default_fds[1]);
	pipe_count = count_pipes(data);
	while (pipe_count > 0)
	{
		pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				dup2(default_fds[0], STDIN_FILENO);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
			}
			else
			{
				dup2(pipe_fd[0], STDIN_FILENO);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			redirect_and_execute(&data, default_fds);
			exit(0);
		}
		else
			wait(NULL);
		update_pipeline(&data);
		pipe_count--;
		i++;
	}
	if (1)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(default_fds[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	redirect_and_execute(&data, default_fds);
	close(pipe_fd[0]);
	restore_defaults(default_fds);
	unlink("./src/builtin/heredoc_tmpfile.txt");
	return (0);
}
