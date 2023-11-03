/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:22:09 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/03 03:11:02 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_env(t_env *env_list)
{
	while (env_list)
	{
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}

int	ft_env(t_data *data)
{
	if (data->next)
	{
		printf("minishell: env: %s:\
			 No such file or directory\n", data->next->content);
		return (127);
	}
	print_env(data->env);
	return (0);
}
