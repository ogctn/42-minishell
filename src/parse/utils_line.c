/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:05:31 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/14 19:55:31 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	is_missing_quoted(char *str, t_env *env)
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
		*(env->exit_code) = 127;
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
		if (d->content)
			free(d->content);
		free(d);
		d = tmp;
	}
}

int	operator_err_control(t_data *data)
{
	t_data	*tmp_1;
	t_data	*tmp_2;

	tmp_1 = data;
	if (tmp_1->type == 1)
		return (printf("minishell$ syntax error near unexpected token '%s'\n",
				tmp_1->content), 127);
	if (ft_last(tmp_1)->type <= 5 && ft_last(tmp_1)->type >= 1)
		return (printf("minishell$ syntax error near unexpected token '%s'\n",
				ft_last(tmp_1)->content), 127);
	while (tmp_1)
	{
		if (tmp_1->type != 0)
		{
			tmp_2 = tmp_1->next;
			if (!ft_strncmp(tmp_1->content, "||", 2)
				|| (tmp_2 && tmp_2->type != 0))
				return (printf("minishell$ syntax error near unexpected \
token '%s'\n", tmp_1->content), 127);
		}
		tmp_1 = tmp_1->next;
	}
	return (0);
}
