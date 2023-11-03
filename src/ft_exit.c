/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:31:13 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/03 03:13:33 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_valid_return(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		if (str[i++ + 1] == '-')
			return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data *d)
{
	printf("exit\n");
	if (d->next)
	{
		if (d->next->next)
		{
			printf("minishell: exit: %s \
too many arguments\n", d->next->next->content);
			exit(255);
		}
		if (is_valid_return(d->next->content))
			exit(ft_atoi(d->next->content));
		else
		{
			printf("minishell: exit: %s: \
numeric argument required\n", d->next->content);
			exit(255);
		}
	}
	else
		exit(0);
}
