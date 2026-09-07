/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:25:51 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/21 13:36:35 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<aio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ps;

	i = 0;
	ps = (unsigned char *)s;
	while (i < n)
	{
		ps[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
/*
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    // Test avec une chaine de caractère
    char str[] = "almost every programmer should know memset!";
    ft_memset (str,'-',  6 * sizeof(str[0]));
    puts (str);
 
    // Test avec un tableau de int
    int t[] = {145478, 1458758, 1421454, 14254585};
    ft_memset(t, 0, 3*sizeof(t[0]));
 
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        printf("%d\n", t[i]);
    }
 
    return EXIT_SUCCESS;
}*/