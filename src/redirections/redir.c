/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:22:35 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/14 16:34:53 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    unlink_node_pair(t_data **head, t_data *first_pair)
{
	t_data  *right_side;
	t_data  *second_pair;
	t_data  *prev_node;

	second_pair = first_pair->next;
	right_side = first_pair->next->next;
	free(second_pair->content);
	free(first_pair->content);
	free(second_pair);
	if (*head == first_pair)
		*head = right_side;
	else
	{
		prev_node = *head;
		while (prev_node && prev_node->next != first_pair)
			prev_node = prev_node->next;
		if (prev_node)
			prev_node->next = right_side;
	}
	free(first_pair);
}

int redir_out(t_data **d)
{
	t_data  *tmp;
	t_data  *to_delete;
	int 	fd;

	tmp = *d;
	while (tmp && tmp->type != 1)
	{
		if (tmp->type == 4 || tmp->type == 5)
		{
			if (tmp->type == 4)
				fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (tmp->type == 5)
				fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			to_delete = tmp;
			tmp = tmp->next->next;
			unlink_node_pair(d, to_delete);
			continue;
		}
		else
			tmp = tmp->next;
	}
	return 0;
}

int redir_in(t_data **d)
{
	t_data  *tmp;
	t_data  *to_delete;
	int 	fd;

	tmp = *d;
	while (tmp && tmp->type != 1)
	{
		if (tmp->type == 2 || tmp->type == 3)
		{
			if (tmp->type == 2)
			{
				fd = open(tmp->next->content, O_RDONLY, 0644);
				if (fd == -1)
					return (printf("minishell: %s: \
					No such file or directory\n", tmp->next->content), -1);
			}
			//else if (tmp->type == 5)
				//heredoc will be implemented
			dup2(fd, STDIN_FILENO);
			close(fd);
			to_delete = tmp;
			tmp = tmp->next->next;
			unlink_node_pair(d, to_delete);
			continue;
		}
		else
			tmp = tmp->next;
	}
	return 0;
}
