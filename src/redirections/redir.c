/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:22:35 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/13 22:46:58 by sgundogd         ###   ########.fr       */
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
	int fd;
		tmp = *d;
	while (tmp && tmp->type != 1)
	{
		if (tmp->type == 4 || tmp->type == 5)
		{
			if (tmp->type == 4)
				fd = open(tmp->next->content, O_RDONLY | O_CREAT | O_TRUNC, 0644);
			if (tmp->type == 5)
				fd = open(tmp->next->content, O_RDONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, 0);
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

// int redir_out(t_data **d)
// {
// 	int		fd;
//     t_data	*current;
// 	t_data	*temp;

// 	current = *d;
//     while (current && current->type != 1)
//     {
//         if (current->type == 4 || current->type == 5)
//         {
// 			if (current->type == 4)
//             	fd = open(current->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (current->type == 5)
//             	fd = open(current->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
//             dup2(fd, 1);
//             close(fd);
//             temp = current->next;
//             current->next = temp->next;
//             free(temp->content);
//             free(temp);
//             temp = current->next;
//             current->next = temp->next;
//             free(temp->content);
//             free(temp);
// 		}
//         else
//             current = current->next;
//     }
//     return (0);
// }

// int		redir_out(t_data *d)
// {
// 	int		fd;
// 	int		i;
// 	int		j;
// 	char	*file;

// 	i = 0;
// 	j = 0;
// 	while (d)
// 	{
// 		if (d->type == 4 || d->type == 5)
// 		{
// 			file = ft_strdup(d->next->content);
// 			if (d->type == 5)
// 				fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
// 			else
// 				fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 			dup2(fd, 1);
// 			close(fd);
// 			free(file);
// 		}
// 		d = d->next;
// 	}
// 	return (0);
// }

