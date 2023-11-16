/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:00:00 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/16 13:13:04 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	join_quote(char *str, int start, int i, char **new)
{
	char	*dnm;

	dnm = ft_substr(str, start, i - start);
	(*new) = ft_strjoin_null((*new), dnm, (*new));
	free(dnm);
}

void	re_create_quote(char *str, char **new, int i)
{
	int		start;
	char	a;

	start = i;
	while (str[i] && !is_quote(str[i]))
		i++;
	join_quote(str, start, i, new);
	a = str[i];
	i++;
	start = i;
	while (str[i] && str[i] != a)
		i++;
	join_quote(str, start, i, new);
	i++;
	start = i;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			re_create_quote(str, new, start);
			return ;
		}
		i++;
	}
	join_quote(str, start, i, new);
}

void	delete_quotes(t_data **data)
{
	t_data	*tmp;
	char	*new;

	if (!(*data))
		return ;
	tmp = (*data);
	while (tmp)
	{
		if (in_quote(tmp->content))
		{
			new = ft_strdup("");
			re_create_quote(tmp->content, &new, 0);
			free(tmp->content);
			tmp->content = new;
		}
		tmp = tmp->next;
	}
}
