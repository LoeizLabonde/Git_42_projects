/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:45:54 by kduroux           #+#    #+#             */
/*   Updated: 2024/05/22 16:17:13 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (ptr_dest <= ptr_src)
	{
		while (n-- > 0)
			*ptr_dest++ = *ptr_src++;
	}
	else
	{
		ptr_dest += (n - 1);
		ptr_src += (n - 1);
		while (n-- > 0)
			*ptr_dest-- = *ptr_src--;
	}
	return (dest);
}
