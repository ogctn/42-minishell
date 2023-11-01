/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:05:31 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/01 13:30:11 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_if_null(char *str)
{
	if (str == NULL)
		exit(3);
	if (str[0] == '\0')
	{
		free(str);
		return (1);
	}
	return (0);
}

int	is_missing_quoted(char *str)
{
	unsigned int	i;
	char			quote;

	quote = 0;
	i = -1;
	while (str[++i])
	{
		if (quote == 0 && (str[i] == '\"' || str[i] == '\''))
			quote = str[i];
		else if (quote == str[i])
			quote = 0;
	}
	if (quote != 0)
	{
		printf("minishell$ parse error near `%c`\n", quote);
		add_history(str);
		free(str);
	}
	return (quote != 0);
}

void	free_data(t_data *d)
{
	t_data	*tmp;

	if (!d)
		return ;
	while (d)
	{
		tmp = d->next;
		free(d->content);
		free(d);
		d = tmp;
	}
}
int operator_control(t_data **total_line)
{
	t_data *tmp_1;
	t_data *tmp_2;
	char	operator;

	tmp_1 = *total_line;
	while (tmp_1)
	{
		if(*(tmp_1->content) == '|' || *(tmp_1->content) == '<' || *(tmp_1->content) == '>')
		{
			tmp_2=tmp_1->next;
			if(tmp_2 && *(tmp_1->content) == *(tmp_2->content))
			{
				tmp_2 = tmp_2->next;
				if(tmp_2 && (*(tmp_1->content) == *(tmp_2->content) || *(tmp_1->content) =='|'))
					printf("minishell$ parse error near \n");
			}
			else
			{
				if(tmp_2 && (*(tmp_2->content) == '|' || *(tmp_2->content) == '<' || *(tmp_2->content) == '>'))
					printf("minishell$ parse error near \n");
			}
		}
		tmp_1= tmp_1->next;
	}
	return(0);
	free_data((*total_line));
}
int operator_control(t_data **total_line)
{
	t_data *tmp_1;
	t_data *tmp_2;

	tmp_1 = *total_line;

	while (tmp_1)
	{
		if(*(tmp_1->content) == '|' || *(tmp_1->content) == '<' || *(tmp_1->content) == '>')
		{
			tmp_2=tmp_1->next;
			if(tmp_2 && *(tmp_1->content) == *(tmp_2->content))
			{
				printf("syntax error\n");
			}
			else if(!ft_strncmp(tmp_1->content,"||",2))
				printf("syntax error\n");
			else if(*(tmp_1->content)== '>' && *(tmp_1->next->content) == '<')
				printf("syntax error\n");
		}
		tmp_1= tmp_1->next;

	}

}
