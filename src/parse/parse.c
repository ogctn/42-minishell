/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:49:51 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/16 13:11:27 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_split_2(char *str, t_data **total_line)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	if (in_quote(str))
	{
		list_add(ft_strdup(str), total_line);
		return ;
	}
	while (str[i])
	{
		if (is_operate(str[i]))
		{
			if (ft_isprint(str[i - 1]) && !is_operate(str[i - 1]))
				list_add(ft_substr(str, start, i - start), total_line);
			if (str[i] == str[i + 1])
			{
				list_add(ft_substr(str, i, 2), total_line);
				i++;
			}
			else
				list_add(ft_substr(str, i, 1), total_line);
			start = i + 1;
		}
		i++;
	}
	if (str[start])
		list_add(ft_substr(str, start, i - start), total_line);
}

void	printit(t_data *d)
{
	int	i;

	i = 0;
	while (d)
	{
		printf("eleman:%d --->\t_%s_\n", i, d->content);
		printf("type: %d\n", d->type);
		d = d->next;
		i++;
	}
}

int	ft_parser(char *str, t_data **total_line, t_env *env_list)
{
	char	**ptr;
	int		i;

	i = -1;
	ptr = ft_spc_split(str);
	if (!ptr || !(*ptr))
		return (free_2d(ptr), 0);
	while (ptr[++i])
		ft_split_2(ptr[i], total_line);
	if (!(*total_line))
		return (free_2d(ptr), 0);
	free_2d(ptr);
	assign_type(total_line);
	init_env_all_data_nodes(total_line, env_list);
	env_variable(total_line, env_list);
	delete_quotes(total_line);
	add_history(str);
	return (operator_err_control(*total_line));
}
