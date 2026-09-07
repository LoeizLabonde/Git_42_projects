/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:25:43 by kduroux           #+#    #+#             */
/*   Updated: 2024/05/23 15:16:58 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;
	char	cc;

	res = NULL;
	i = 0;
	cc = (char) c;
	while (s[i])
	{
		if (s[i] == cc)
		{
			res = (char *) &s[i];
		}
		i++;
	}
	if (s[i] == cc)
		res = (char *) &s[i];
	return (res);
}
