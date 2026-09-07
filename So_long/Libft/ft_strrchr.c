/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:01:46 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/22 15:06:11 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		len;
	char	*p_str;
	char	cc;

	cc = (char)c;
	p_str = (char *)str;
	len = ft_strlen((char *)str);
	if (cc == '\0')
		return (p_str + len);
	while (len >= 0)
	{
		if (*(p_str + len) == cc)
			return (&p_str[len]);
		len--;
	}
	return (NULL);
}
