/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:36:30 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/09 16:55:08 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_only_flag(char *arg, int *flag)
{
	int	i;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	*flag = 1;
	return (1);
}

int	ft_echo(t_data *d)
{
	int	flag;

	flag = 0;
	d = d->next;
	while (d && is_only_flag(d->content, &flag))
		d = d->next;
	if (!d)
		return (1);
	while (d)
	{
		printf("%s", d->content);
		d = d->next;
		if (d)
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}
