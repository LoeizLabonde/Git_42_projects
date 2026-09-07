/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:32:27 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/27 15:53:41 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	ac;

	ac = (char)c;
	if (ac == '\0')
		return ((char *)(str + ft_strlen((char *)str)));
	while (*str != '\0')
	{
		if (*str == ac)
			return ((char *)(str));
		str++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char *str;
	char *test;
	int A ;
	int zero;

	str = "tripouille";
	test = "";
	A = 65;
	zero = 0;
	
	printf("A : 012345678B = %s.\n", ft_strchr(test,A));
	printf("A : 012345678A = %s.\n", ft_strchr(str,A));
	printf("test : %p.\n", test);
	printf("zero : 012B = %p.\n", ft_strchr(test, zero));
	printf("tripouille, 't' + 256 = %p.\n", ft_strchr(str, 't' + 256));	


}*/