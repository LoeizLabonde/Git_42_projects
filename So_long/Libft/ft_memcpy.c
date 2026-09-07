/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:24:59 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/27 15:49:27 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ps;
	unsigned char	*as;

	ps = (unsigned char *)dest;
	as = (unsigned char *)src;
	if (!dest && !src)
		return (dest);
	while (n > 0)
	{
		*(ps++) = *(as++);
		n--;
	}
	return (dest);
}
