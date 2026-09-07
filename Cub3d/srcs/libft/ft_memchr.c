/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:14:35 by kduroux           #+#    #+#             */
/*   Updated: 2024/05/28 13:51:27 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	sc;
	size_t			i;

	str = (unsigned char *) s;
	sc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == sc)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
