/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:38:51 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/03 07:14:42 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_counter(char const	*s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			while (s[i + 1] && s[i + 1] != s[i])
				i++;
			count++;
		}
		else if (s[i] == ' ' && s[i + 1] != ' ' && !is_quote(s[i + 1]))
			count++;
		i++;
	}
	if (is_quote(s[0]) || s[0] == ' ')
		return (count);
	return (count + 1);
}

static void	ft_update(const char *s, int start, int *end)
{
	int		end_idx;
	char	c;

	end_idx = *end;
	c = s[end_idx];
	if (!is_quote(s[start]))
	{
		while (!is_operate(s[start]) && s[start] != c)
			start++;
		if (end_idx != start)
		{
			(*end) = start + 1;
			return ;
		}
	}
	start++;
	while (s[start] && s[start] != c)
		start++;
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

static char	**ft_string(char const *s, char **ptr)
{
	int	end;
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (s[start])
	{
		while (s[start] == ' ')
			start++;
		end = start;
		if (s[start] == '"' || s[start] == '\'')
			ft_update(s, start, &end);
		else
		{
			while (s[end] != ' ' && s[end])
			{
				if (s[end] == '"' || s[end] == '\'')
				{
					ft_update(s, start, &end);
					break ;
				}
				end++;
			}
		}
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
	ptr = (char **)malloc(sizeof(char *) * (ft_counter(s) + 1));
	if (!ptr)
		return (NULL);
	return (ft_string(s, ptr));
}
