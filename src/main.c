/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:24:32 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/10 13:24:13 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	main_loop(t_env *env_list)
{
	t_data	*data;
	char	*line;

	while (1)
	{
		data = NULL;
		line = readline(MINISHELL);
		if (!line)
			exit(write(1, "exit\n", 5) - 5);
		if (check_if_null(line) || is_missing_quoted(line))
			continue ;
		ft_parser(line, &data, env_list);
		printit(data);
		executer(data);
		free(line);
		free_data(data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*env_list;

	if (ac != 1 || av[1] != NULL || !env || !(*env))
		return (1);
	get_signals();
	get_default_env(&env_list, env);
	mini_clear(env_list);
	main_loop(env_list);
	return (0);
}
