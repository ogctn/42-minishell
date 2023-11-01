/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:49:51 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/01 11:06:07 by sgundogd         ###   ########.fr       */
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
		{
		if((*total_line))
		{
			tmp = ft_last(*total_line);
			tmp->next = ft_create(ft_strdup(str));
		}
		else
			(*total_line) = ft_create(ft_strdup(str));
		}
		return;
	}
	while (str[i])
	{
		if(str[i] == '|' ||str[i] == '<' ||str[i] == '>')
		{
		if(ft_isprint(str[i-1]) && str[i-1] != '<' && str[i-1] != '>' && str[i-1] != '|')
		{
			if((*total_line))
			{
				tmp = ft_last(*total_line);
				tmp->next = ft_create(ft_substr(str,start,i-start));
			}
			else
				(*total_line) = ft_create(ft_substr(str,start,i-start));
			tmp = ft_last(*total_line);
			if(str[i] == str[i+1])
			{
				tmp->next = ft_create(ft_substr(str,i,2));
				i++;
			}
			else
				tmp->next = ft_create(ft_substr(str,i,1));
		}
		else
		{
			if((*total_line))
			{
				tmp = ft_last(*total_line);
				if(str[i] == str[i+1])
				{

				tmp->next = ft_create(ft_substr(str,i,2));
				i++;
				}
				else
					tmp->next = ft_create(ft_substr(str,i,1));
			}
			else
				if(str[i] == str[i+1])
				{

				(*total_line) = ft_create(ft_substr(str,i,2));
				i++;
				}
				else
					(*total_line) = ft_create(ft_substr(str,i,1));
		}
		start = i+1;
		}
		i++;
	}
	if(str[start])
	{
		if((*total_line))
		{
			tmp = ft_last(*total_line);
			tmp->next = ft_create(ft_substr(str,start,i-start));
		}
		else
			(*total_line) = ft_create(ft_substr(str,start,i-start));
	}
}


void ft_parser(char *str,t_data **total_line)
{
	char **ptr;
	int i;

	i = -1;
	ptr = ft_spc_split(str);
	while(ptr[++i])
		ft_split_2(ptr[i],total_line);
	free_2d(ptr);
}


