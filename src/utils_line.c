/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:05:31 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/06 04:53:35 by ogcetin          ###   ########.fr       */
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
	d = NULL;
}

void	mini_clear(t_env *env)
{
	pid_t	pid;
	char	*clear_path;
	char	*envp[2];

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
