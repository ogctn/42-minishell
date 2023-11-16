/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:22:35 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/16 13:44:52 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    unlink_node_pair(t_data **head, t_data *redir_node)
{
	t_data  *after_file_node;
	t_data  *file_name;
	t_data  *tmp;

	file_name = redir_node->next;
	after_file_node = redir_node->next->next;
	free(file_name->content);
	free(redir_node->content);
	free(file_name);
	if (*head == redir_node)
		*head = after_file_node;
	else
	{
		tmp = *head;
		while (tmp->next != redir_node)
			tmp = tmp->next;
		tmp->next = after_file_node;
	}
	free(redir_node);
}

int redir_out(t_data **head, t_data *d)
{
	int 	fd;

	if (d->type == 4)
		fd = open(d->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (d->type == 5)
		fd = open(d->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ft_putstr_fd("minishell: file open error.\n", 2), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	unlink_node_pair(head , d);
	return (0);
}

int redir_in(t_data **head, t_data *d)
{
	t_data  *to_delete;
	int 	fd;

	if (d->type == 2)
	{
		if (!d->next->content[0])
			return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), 1);
		fd = open(d->next->content, O_RDONLY, 0644);
		if (fd == -1)
			return (printf("minishell: %s: \
No such file or directory\n", d->next->content), 1);
	}
	//else if ((*d)->type == 3)
		//heredoc will be implemented
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink_node_pair(head, d);
	return (0);
}
