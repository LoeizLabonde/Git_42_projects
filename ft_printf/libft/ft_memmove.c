/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:52:48 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/27 15:50:38 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ps;
	unsigned char	*as;

	i = 0;
	if (!dest && !src)
		return (NULL);
	ps = (unsigned char *)dest;
	as = (unsigned char *)src;
	if (ps < as)
	{
		while (i < n)
		{
			ps[i] = (unsigned char)as[i];
			i++;
		}
		return (dest);
	}
	i = n;
	while (i > 0)
	{
		ps[i - 1] = (unsigned char)as[i - 1];
		i--;
	}
	return (dest);
}
