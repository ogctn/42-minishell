/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:38:51 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/16 20:16:52 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_counter(char const	*s)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		else if (s[i] == ' ' && s[i + 1]
			&& s[i + 1] != ' ' && !is_quote(s[i + 1]))
			count++;
		i++;
	}
	if (is_quote(s[0]) || s[0] == ' ')
		return (count);
	return (count + 1);
}

static void	ft_update(const char *s, int start, int *end)
{
	char	c;

	c = s[(*end)];
	if (!is_quote(s[start]))
	{
		if (find_end_1(&start, s, end, c))
			return ;
	}
	start++;
	while (s[start] && s[start] != c)
		start++;
	if (s[start])
		start++;
	while (s[start] && s[start] != ' ' && !is_operate(s[start]))
	{
		if (is_quote(s[start]))
		{
			ft_update(s, start, end);
			return ;
		}
		start++;
	}
	(*end) = start;
}

static int	split_loop(char const *s, int *start, int *end)
{
	while (s[(*start)] == ' ')
		(*start)++;
	if (!s[(*start)])
		return (1);
	*end = *start;
	if (s[(*start)] == '"' || s[(*start)] == '\'')
		ft_update(s, (*start), end);
	else
	{
		while (s[*end] && s[*end] != ' ')
		{
			if (s[*end] == '"' || s[*end] == '\'')
			{
				ft_update(s, (*start), end);
				break ;
			}
			(*end)++;
		}
	}
	return (0);
}

static char	**ft_string(char const *s, char **ptr)
{
	int	end;
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (s[start])
	{
		if (split_loop(s, &start, &end))
			break ;
		ptr[i] = ft_substr(s, start, end - start);
		start = end;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_spc_split(char const *s)
{
	char	**ptr;

	if (!s || s[0] == 0)
	{
		ptr = ft_calloc(1, sizeof(char *));
		ptr[0] = 0;
		return (ptr);
	}
	ptr = (char **)ft_calloc(sizeof(char *), (ft_counter(s) + 1));
	if (!ptr)
		return (NULL);
	return (ft_string(s, ptr));
}
