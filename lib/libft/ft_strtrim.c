/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogcetin <ogcetin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:49:58 by ogcetin           #+#    #+#             */
/*   Updated: 2023/01/27 23:04:02 by ogcetin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;

	if (!s1 || !set)
		return (0);
	first = 0;
	while (ft_strchr(set, s1[first]) && s1[first] != '\0')
		first++;
	last = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[last]) && last != 0)
		last--;
	if ((int)(last - first + 1) <= 0)
		return (ft_strdup(""));
	return (ft_substr(s1, first, (last - first + 1)));
}
