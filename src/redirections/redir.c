/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:22:35 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/17 03:21:45 by sgundogd         ###   ########.fr       */
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

void	heredoc_create_infile(t_data *d, int default_fds[2])
{
	int		fd;
	int		tmp_fd[2];
	char	*line;
	int		pid;

	copy_default_fd(&tmp_fd[0], &tmp_fd[1]);
	pid = fork();
	if (pid == 0)
	{
		dup2(default_fds[0], STDIN_FILENO);
		dup2(default_fds[1], STDOUT_FILENO);
		fd = open("./src/builtin/heredoc_tmpfile.txt", O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: file open error.\n", 2);
			exit(1);
		}
		while (1)
		{
			line = readline("> ");
			if (!ft_strncmp(line, d->next->content, ft_strlen(d->next->content))
				&& ft_strlen(line) == ft_strlen(d->next->content))
			{
				free(line);
				break ;
			}
			ft_putendl_fd(line, fd);
			free(line);
		}
		close(fd);
		exit(0);
	}
	wait(NULL);
	restore_defaults(tmp_fd);
}

int	redir_in(t_data **head, t_data *d, int default_fds[2])
{
	int			fd;

	fd = 0;
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
		heredoc_create_infile(d, default_fds);
		fd = open("./src/builtin/heredoc_tmpfile.txt", O_RDONLY, 0644);
		if (fd == -1)
			return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink_node_pair(head, d);
	return (0);
}
