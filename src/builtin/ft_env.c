/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:22:09 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/14 19:34:29 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	are_valid_env_parameters(t_data *d)
{
	char	*str;

	d = d->next;
	if (!d || d->type == 1)
		return (1);
	str = d->content;
	if (str[0] == '-' && str[1])
	{
		printf("Illegal option -- %c\n", str[0]);
		printf("usage: env [name=value ...] [name=value ...] ...\n");
		return (0);
	}
	while (d && d->type != 1)
	{
		str = d->content;
		if (!ft_strchr(str, '='))
		{
			printf("env: --%s: No such file or directory\n", str);
			return (0);
		}
		d = d->next;
	}
	return (1);
}

void	print_env(t_env *env_list)
{
	while (env_list)
	{
		if (ft_strchr(env_list->content, '='))
			printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}

int	ft_env(t_data *data)
{
	if (are_valid_env_parameters(data))
	{
		if (data->env)
			print_env(data->env);
		while (data->next && data->next->type != 1)
		{
			data = data->next;
			printf("%s\n", data->content);
		}
		return (0);
	}
	return (1);
}
