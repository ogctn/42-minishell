/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:04:13 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/16 19:20:03 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**data_to_double_arr(t_data *d)
{
	char	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(sizeof(char *), (ft_lstsize(d) + 1));
	ret[ft_lstsize(d)] = NULL;
	while (d && d->type != 1)
	{
		ret[i++] = ft_strdup(d->content);
		d = d->next;
	}
	return (ret);
}

void	copy_default_fd(int *default_in, int *default_out)
{
	*default_in = dup(STDIN_FILENO);
	*default_out = dup(STDOUT_FILENO);
}

void	restore_defaults(int default_fds[2])
{
	dup2(default_fds[0], STDIN_FILENO);
	dup2(default_fds[1], STDOUT_FILENO);
	close(default_fds[0]);
	close(default_fds[1]);
}

int	count_pipes(t_data *d)
{
	int	count;

	count = 0;
	while (d)
	{
		if (d->type == 1)
			count++;
		d = d->next;
	}
	return (count);
}

void	update_pipeline(t_data **d)
{
	t_data	*tmp;

	tmp = *d;
	while (tmp && tmp->type != 1)
		tmp = tmp->next;
	if (tmp)
	{
		tmp = tmp->next;
		while (*d && *d != tmp && (*d)->type != 1)
			*d = (*d)->next;
		*d = (*d)->next;
	}
}
