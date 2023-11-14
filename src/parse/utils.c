/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:49:00 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/14 20:08:59 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_operate(char s)
{
	if (s == '<' || s == '>' || s == '|')
		return (1);
	return (0);
}

int	is_quote(char s)
{
	if (s == '\'' || s == '"')
		return (1);
	return (0);
}

int	in_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	mini_clear(t_env *env)
{
	pid_t	pid;
	char	*clear_path;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		clear_path = path_finder("clear", env);
		execve(clear_path, NULL, env_to_double_arr(env));
	}
	else
		wait(NULL);
}
