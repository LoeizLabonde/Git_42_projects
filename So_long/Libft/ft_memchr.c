/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:21:24 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/23 12:20:49 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<aio.h>
#include<stdlib.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p_s;

	p_s = (unsigned char *)s;
	c = (unsigned char)c;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (p_s[i] == c)
			return ((void *)(p_s + i));
		i++;
	}
	return (NULL);
}
