/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:38:22 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/23 11:05:11 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdlib.h>

static char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	dest_len;

	dest_len = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
			dest[dest_len + i] = src[i];
			i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		t;
	int		i;

	i = 0;
	t = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	join = (char *) malloc(t * sizeof(char) + 1);
	if (!join)
		return (NULL);
	*join = 0;
	ft_strcat(join, (char *)s1);
	ft_strcat(join, (char *)s2);
	return (join);
}
