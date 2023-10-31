/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:24:32 by sgundogd          #+#    #+#             */
/*   Updated: 2023/11/01 02:16:24 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_control(t_data **total_line)
{
	t_data *tmp_1;
	t_data *tmp_2;

	tmp_1 = *total_line;

	while (tmp_1)
	{
		if(*(tmp_1->content) == '|' || *(tmp_1->content) == '<' || *(tmp_1->content) == '>')
		{
			tmp_2=tmp_1->next;
			if(tmp_2 && *(tmp_1->content) == *(tmp_2->content))
			{
				tmp_2 = tmp_2->next;
				if(tmp_2 && (*(tmp_1->content) == *(tmp_2->content) || *(tmp_1->content) =='|'))
					printf("error 1\n");
			}
			else
			{
				if(tmp_2 && (*(tmp_2->content) == '|' || *(tmp_2->content) == '<' || *(tmp_2->content) == '>'))
					printf("error 2\n");
			}
		}
		tmp_1= tmp_1->next;

	}

}

void	printit(t_data *d)
{
	int i = 0;
	while (d)
	{
		printf("\neleman:%d --->\t%s\n", i, d->content);
		printf("type: %d\n", d->type);
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
		ft_parser(line, &data);
		printit(data);	// to print the linked list
		if (check_if_null(line) || is_missing_quoted(line)) // to check if there are missing quotes or null
			continue ;
		// to continue the loop if there are missing quotes or null
		add_history(line);
		executer(data, env); // to execute the command
		free_data(data); // to free the linked list
		free(line); // to free the line from the previous iteration
	}
	return (0);
}
