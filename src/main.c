/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:24:32 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/01 13:17:21 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **env)
{
	t_env	*env_list;
	t_data	*data;
	char	*line;

	if (ac != 1 || av[1] != NULL || !env || !(*env)) // to check if there is no argument
		return (1);
	suppress_output();
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	get_default_env(&env_list, env);
	mini_clear(env_list);
	while (1)
	{
		data = NULL;
		line = readline("\033[0;36mminishell$ \033[0m");
		if (!line)
			exit(1);
		if (check_if_null(line) || is_missing_quoted(line))
			continue ;
		if(ft_parser(line, &data,env_list))
			executer(data); 
		free_data(data); 
		free(line);
	}
	return (0); 
}
