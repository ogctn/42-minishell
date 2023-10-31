/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:38:51 by sgundogd          #+#    #+#             */
/*   Updated: 2023/10/31 20:11:35 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_counter(char const	*s)
{
	int		i;
	int		count;
	char	c;
	int		end;

	i = 0;
	count = 0;
	end = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			end = i+1;
			c = s[i];
			while(s[end]!=c && s[end])
				end++;
			count++;
			i = end - 1;
		}
		else if (s[i] == ' ' && s[i+1] != ' ' && s[i+1] != '\'' && s[i+1] != '"' && s[i+1])
			count++;
		i++;
	}
	if (s[0] == '"' || s[0] == '\'' || s[0] == ' ')
		return (count);
	return (count + 1);
}

static void ft_update(const char *s, int start2, int *end)
{
	int end2 = *end;
	char c = s[end2];
	if(s[start2]!= '"'&& s[start2] != '\'')
	{
		while (!is_operate(s[start2]) && s[start2] != c)
			start2++;
		if(end2 != start2)
		{
			(*end) = start2 + 1;
			return;
		}
	}
	start2++;
	while(s[start2] && s[start2] != c)
		start2++;
	start2++;
	if(s[start2]== '"'|| s[start2] == '\'')
		ft_update(s,start2,end);
	else
	{
	while (s[start2] && s[start2] != ' ' && !is_operate(s[start2]))
		start2++;
	(*end) = start2;
	}

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
		if(s[start] == '"' || s[start] == '\'')
			ft_update(s,start,&end);
		else
		{
			while (s[end] != ' ' && s[end])
			{
				if(s[end] == '"' || s[end] == '\'')
				{
					ft_update(s,start,&end);
					break;
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
	return (ft_string(s,ptr));
}
