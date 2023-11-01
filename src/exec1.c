/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:17:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/01 12:41:35 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**list_to_double_arr(t_data *d)
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

void	exec_simple(t_data *d, char **env)
{
	char	**args;
	pid_t	pid;
	char 	*cmd_path;
	
	pid = fork();
	if (pid == 0)
	{
		if (is_buitin(d->content))
		{
			exec_builtin(d, env);
			exit(1);
		}
		args = list_to_double_arr(d);
		execve(path_finder(args[0], env), args, env);	
	}
	wait(NULL);
}

void	count_char(char *read_line, char c, int *counter)
{
	int	i;

	i = -1;
	while (read_line[++i])
		if (read_line[i] == c)
			(*counter)++;
}

int	executer(t_data *data, char **env)
{
	char *full_line;
	int	pipe_count;
	int	redir_count;
	int	redir_type;

	pipe_count = 0;
	//count_char(read_line, '|', &pipe_count);	// will be changed
	//if (pipe_count == 0)
	//{
		//if (redir_type == 0)
			exec_simple(data, env);
		// else if (redir_type == 1)
		// 	exec_redir_out(full_line, env);
		// else if (redir_type == 2)
		// 	exec_redir_in(full_line, env);
	//}
	//else
		//if (exec_pipe(full_line, env))
	//		return (-1);
	return (0);
}
