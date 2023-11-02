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

void	printit(t_data *d)
{
	int i = 0;
	while (d)
	{
		printf("\neleman:%d --->\t%s\n", i, d->content);
		//printf("type: %d\n", d->type);
		d = d->next;
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*line;
	int 	i;

	if (ac != 1 || av[1] != NULL || !env) // to check if there is no argument
		return (1);
	suppress_output();
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	while (1)
	{
		i = 0;
		line = readline("minishell$ ");
		if (!line) // to check if SIGQUIT is pressed
			exit(1);
		data = NULL;
		if (check_if_null(line) || is_missing_quoted(line)) // to check if there are missing quotes or null
			continue ;
		add_history(line);
		ft_parser(line, &data);
		printit(data);	// to print the linked list
		// to continue the loop if there are missing quotes or null
		if(operator_err_control(data))
			executer(data, env); // to execute the command
		free_data(data); // to free the linked list
		free(line); // to free the line from the previous iteration
	}
	return (0);
}
