/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:17:46 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/23 16:47:43 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdio.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (s && f)
	{
		i = 0;
		while (*s)
			f(i++, s++);
	}
}
/*
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int		i;
	void	*res;

	i = 0;
	if (!s)
		return ;
	res = s;
	while (s[i] != '\0')
	{
		f(i, res);
		i++;
		res++;
	}
	*s = '\0';
}

void
iter(unsigned int i, char * s) {
	*s += i;
	printf("plop\n");
}

int	main(void)
{
	char s[] = "00000000000";
	ft_striteri(s, &iter);
}*/