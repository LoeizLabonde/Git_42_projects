/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:07:14 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/22 16:27:21 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include "libft.h"

static char	*ft_str_n(size_t n)
{
	char	*str;

	str = (char *) malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*sub_p;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen((char *)s))
		len = 0;
	else if (len > (ft_strlen((char *)s) - start))
		len = ft_strlen((char *)s) - start;
	sub = ft_str_n(len);
	if (!sub)
		return (NULL);
	s += start;
	sub_p = sub;
	sub[len] = '\0';
	while (len-- && s)
		*sub++ = *s++;
	return (sub_p);
}
