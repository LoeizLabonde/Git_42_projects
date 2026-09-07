/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:58:38 by kduroux           #+#    #+#             */
/*   Updated: 2024/05/22 16:28:42 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	ptr_dest = (unsigned char *) dest;
	ptr_src = (unsigned char *) src;
	if (!dest && !src)
		return (dest);
	while (n > 0)
	{
		*(ptr_dest++) = *(ptr_src++);
		n--;
	}
	return (dest);
}
