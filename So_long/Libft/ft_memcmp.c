/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:50:12 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/22 15:03:03 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<aio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p_s1;
	unsigned char	*p_s2;

	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (p_s1[i] != p_s2[i])
			return ((unsigned char)p_s1[i] - (unsigned char)p_s2[i]);
		i++;
	}
	return (0);
}
