/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:01:53 by ogcetin           #+#    #+#             */
/*   Updated: 2022/12/22 21:17:35 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int a)
{
	if (a >= 'a' && a <= 'z')
		a -= 32;
	return (a);
}
