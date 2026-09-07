/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:23:13 by kduroux           #+#    #+#             */
/*   Updated: 2024/05/22 13:37:16 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t siz)
{
	size_t	i;
	size_t	dest_len;

	i = 0;
	if (!dest && !siz)
		return (ft_strlen(src) + siz);
	dest_len = ft_strlen(dest);
	if (dest_len >= siz)
		return (ft_strlen(src) + siz);
	if (siz == 0)
		return (ft_strlen(src));
	while (src[i] && i < (siz - dest_len - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (ft_strlen(src) + dest_len);
}
