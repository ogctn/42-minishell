/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:22:35 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/17 11:06:56 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unlink_node_pair(t_data **head, t_data *redir_node)
{
	t_data	*after_file_node;
	t_data	*file_name;
	t_data	*tmp;

	file_name = redir_node->next;
	after_file_node = redir_node->next->next;
	if (*head == redir_node)
		*head = after_file_node;
	else
	{
		tmp = *head;
		while (tmp->next != redir_node)
			tmp = tmp->next;
		tmp->next = after_file_node;
	}
}

void	ft_error_here(void)
{
	ft_putstr_fd("minishell: file open error.\n", 2);
	exit(1);
}

int	redir_out(t_data **head, t_data *d)
{
	int	fd;

	if (d->type == 4)
		fd = open(d->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(d->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ft_putstr_fd("minishell: file open error.\n", 2), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	unlink_node_pair(head, d);
	return (0);
}

char	*heredoc_create_infile(t_data *d, int default_fds[2])
{
	int		fd;
	int		tmp_fd[2];
	int		pid;
	char	*path_here;

	copy_default_fd(&tmp_fd[0], &tmp_fd[1]);
	path_here = get_env_value(d->env, "HOME");
	path_here = ft_strjoin(path_here, "/heredoc_tmpfile.txt");
	pid = fork();
	if (pid == 0)
	{
		dup2(default_fds[0], STDIN_FILENO);
		dup2(default_fds[1], STDOUT_FILENO);
		fd = open(path_here, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			ft_error_here();
		heredoc_loop(d->next->content, fd);
		close(fd);
		exit(0);
	}
	wait(NULL);
	restore_defaults(tmp_fd);
	return (path_here);
}

int	redir_in(t_data **head, t_data *d, int default_fds[2])
{
	int		fd;
	char	*path_here;

	fd = 0;
	path_here = NULL;
	if (d->type == 2)
	{
		if (!d->next->content[0])
			return (dup2(2, STDOUT_FILENO),
				ft_putstr_fd("minishell: ambiguous redirect\n", 2), 1);
		fd = open(d->next->content, O_RDONLY, 0644);
		if (fd == -1)
			return (dup2(2, STDOUT_FILENO), printf("minishell: %s: \
No such file or directory\n", d->next->content), 1);
	}
	else if (d->type == 3)
	{
		path_here = heredoc_create_infile(d, default_fds);
		fd = open(path_here, O_RDONLY, 0644);
		if (fd == -1)
			return (free(path_here), 1);
	}
	redir_in_continued(d->type, path_here, fd);
	unlink_node_pair(head, d);
	return (0);
}
