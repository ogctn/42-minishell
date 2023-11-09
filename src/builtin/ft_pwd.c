/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:42:44 by ogcetin           #+#    #+#             */
/*   Updated: 2023/11/09 20:07:21 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (!dir)
	{
		printf("minishell: pwd: \
An error occurred in the getcwd() function call.\n");
		return (1);
	}
	printf("%s\n", dir);
	free(dir);
	return (0);
}
