/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:49:51 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/01 12:04:20 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_split_2(char *str, t_data **total_line)
{
	int i = 0;
	int counter = 0;
	int start = 0;
	int j = 0;
	t_data *tmp;
	if(in_quote(str))
	{
		if(ft_strlen(str) > 2)
			list_add(ft_strdup(str),total_line);
		return;
	}
	while (str[i])
	{
		if(is_operate(str[i]))
		{
			if(ft_isprint(str[i-1]) && !is_operate(str[i-1]))
				list_add(ft_substr(str,start,i-start), total_line);
			tmp = ft_last(*total_line);
			if(str[i] == str[i+1])
			{
				list_add(ft_substr(str,i,2),total_line);
				i++;
			}
			else
				list_add(ft_substr(str,i,1),total_line);
		start = i+1;
		}
		i++;
	}
	if(str[start])
		list_add(ft_substr(str,start,i-start),total_line);

}

void	printit(t_data *d)
{
	int i = 0;
	while (d)
	{
		printf("\neleman:%d --->\t%s\n", i, d->content);
		printf("type: %d\n", d->type);
		d = d->next;
		i++;
	}
}

int ft_parser(char *str,t_data **total_line, char **env)
{
	char **ptr;
	int i;
	i = -1;
	ptr = ft_spc_split(str);
	while(ptr[++i])
		ft_split_2(ptr[i],total_line);
	free_2d(ptr);
	assign_type(total_line);
	//printit(*total_line);
	env_variable(total_line, env);
	return(operator_err_control(*total_line));
}
