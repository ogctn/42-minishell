/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:15:59 by ogcetin           #+#    #+#             */
/*   Updated: 2023/01/27 18:14:19 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	void	*new;
	size_t	i;

	i = ft_strlen(s1) + 1;
	new = (char *)ft_calloc(i, sizeof(*s1));
	if (!new)
		return (0);
	ft_memcpy(new, s1, i * sizeof(*s1));
	return ((char *)new);
}
