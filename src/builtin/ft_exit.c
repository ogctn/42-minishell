/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:31:13 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/09 16:55:12 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_numeric_return(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		++i;
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

int	are_valid_exit_params(t_data *d)
{
	d = d->next;
	if (!is_numeric_return(d->content))
	{
		printf("minishell: exit: %s: \
numeric argument required\n", d->content);
		exit(255);
	}
	if (d->next)
		printf("minishell: exit: too many arguments\n");
	else
		exit(ft_atoi(d->content));
	return (255);
}

int	ft_exit(t_data *d)
{
	printf("exit\n");
	if (d->next)
	{
		if (are_valid_exit_params(d))
			return (255);
	}
	else
		exit(0);
	return (0);
}
