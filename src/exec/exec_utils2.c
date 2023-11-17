/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:59:35 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/17 10:47:19 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child_part(t_data *d)
{
	char	**args;
	char	*cmd_path;

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

void	sub_exec(t_data *d, int i, int pipe_fd[2], int default_fds[2])
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
	redirect_and_execute(&d, default_fds);
	exit(0);
}

void	sub_exec2(t_data *d, int pipe_fd[2], int default_fds[2])
{
	char	*path_here;

	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(default_fds[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	redirect_and_execute(&d, default_fds);
	close(pipe_fd[0]);
	restore_defaults(default_fds);
	path_here = get_env_value(d->env, "HOME");
	path_here = ft_strjoin(path_here, "/heredoc_tmpfile.txt");
	unlink(path_here);
	free(path_here);
}
