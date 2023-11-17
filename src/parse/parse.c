/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:49:51 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/17 00:54:47 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_end_1(int *start, const char *s, int *end, char c)
{
	int		end_idx;

	end_idx = *end;
	while (!is_operate(s[*start]) && s[*start] != c)
		(*start)++;
	if (end_idx != (*start))
	{
		(*end) = (*start) + 1;
		return (1);
	}
	return (0);
}

void	ft_split_2(char *str, t_data **total_line)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	if (in_quote(str))
		return (list_add(ft_strdup(str), total_line));
	while (str[i])
	{
		if (is_operate(str[i]))
		{
			if (i && ft_isprint(str[i - 1]) && !is_operate(str[i - 1]))
				list_add(ft_substr(str, start, i - start), total_line);
			if (str[i] == str[i + 1])
				list_add(ft_substr(str, i++, 2), total_line);
			else
				list_add(ft_substr(str, i, 1), total_line);
			start = i + 1;
		}
		i++;
	}
	if (str[start])
		list_add(ft_substr(str, start, i - start), total_line);
}

void	printit(t_data *d, char *s)
{
	int	i;

	i = 0;
	dprintf(2, "---------	%s	----------\n", s);
	while (d)
	{
		dprintf(2, "eleman:%d --->\t_%s_\n", i, d->content);
		dprintf(2, "type: %d\n", d->type);
		d = d->next;
		i++;
	}
	dprintf(2, "------------------------\n");
}

int	ft_parser(char *str, t_data **total_line, t_env *env_list)
{
	char	**ptr;
	int		i;

	i = -1;
	add_history(str);
	ptr = ft_spc_split(str);
	if (!ptr || !(*ptr))
		return (free_2d(ptr), -1);
	while (ptr[++i])
		ft_split_2(ptr[i], total_line);
	if (!(*total_line))
		return (free_2d(ptr), -1);
	free_2d(ptr);
	assign_type(total_line);
	init_env_all_data_nodes(total_line, env_list);
	env_variable(total_line, env_list);
	delete_quotes(total_line);
	return (operator_err_control(*total_line));
}
