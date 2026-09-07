/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:43:16 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/23 11:23:10 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdlib.h>

static size_t	get_digits(int n)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*itoa;
	size_t		digits;
	long int	num;

	num = n;
	digits = get_digits(n);
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	itoa = (char *)malloc(sizeof(char) * (digits + 1));
	if (!itoa)
		return (NULL);
	itoa[digits] = 0;
	while (digits--)
	{
		itoa[digits] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		itoa[0] = '-';
	return (itoa);
}
