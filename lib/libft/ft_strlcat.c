/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:18:31 by ogcetin           #+#    #+#             */
/*   Updated: 2023/01/04 20:40:46 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dest_size)
{
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (!dst && !dest_size)
		return (0);
	if (len_dst >= dest_size)
		return (len_src + dest_size);
	ft_strlcpy((dst + len_dst), src, dest_size - len_dst);
	return (len_dst + len_src);
}
