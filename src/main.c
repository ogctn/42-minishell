/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:24:32 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/17 09:41:23 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	main_loop(t_env *env_list)
{
	t_data	*data;
	char	*line;
	int		default_fds[2];
	int		a;

	copy_default_fd(&default_fds[0], &default_fds[1]);
	while (1)
	{
		restore_defaults(default_fds);
		data = NULL;
		line = readline(MINISHELL);
		if (!line)
			exit(printf("\033[A%sexit\n", MINISHELL) - 61);
		if (check_if_null(line) || is_missing_quoted(line, env_list))
			continue ;
		a = ft_parser(line, &data, env_list);
		if (a != -1)
		{
			*(data->env->exit_code) = a;
			if (*(data->env->exit_code) == 0)
				executer(data);
		}
		free(line);
		free_data(data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*env_list;
	int		ercode;

	ercode = 0;
	if (ac != 1 || av[1] != NULL || !env || !(*env))
		return (1);
	get_signals();
	get_default_env(&env_list, env, &ercode);
	mini_clear(env_list);
	main_loop(env_list);
	return (0);
}
