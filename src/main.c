/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:24:32 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/04 19:25:17 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_control(t_data **total_line)
{
	t_data	*tmp_1;
	t_data	*tmp_2;

	tmp_1 = *total_line;
	while (tmp_1)
	{
		if (*(tmp_1->content) == '|' || *(tmp_1->content) == '<' \
					|| *(tmp_1->content) == '>')
		{
			tmp_2 = tmp_1->next;
			if (tmp_2 && *(tmp_1->content) == *(tmp_2->content))
			{
				tmp_2 = tmp_2->next;
				if (tmp_2 && (*(tmp_1->content) == *(tmp_2->content) \
					|| *(tmp_1->content) == '|'))
					printf("error 1\n");
			}
			else
				if (tmp_2 && (*(tmp_2->content) == '|' \
					|| *(tmp_2->content) == '<' || *(tmp_2->content) == '>'))
					printf("error 2\n");
		}
		tmp_1 = tmp_1->next;
	}
}

// FREE_ENV_LIST UNUTMA
int	main(int ac, char **av, char **env)
{
	t_env	*env_list;
	t_data	*data;
	char	*line;

	if (ac != 1 || av[1] != NULL || !env || !(*env))
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
		ft_parser(line, &data, env_list);
		executer(data);
		free(line);
		free_data(data);
	}
	return (0);
}
