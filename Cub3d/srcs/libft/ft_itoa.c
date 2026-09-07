/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:31:18 by kduroux           #+#    #+#             */
/*   Updated: 2024/05/28 13:03:46 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_nbrlen(int n)
{
	int	count_number;
	int	is_neg;

	count_number = 0;
	is_neg = 0;
	if (n < 0)
	{
		is_neg = 1;
		n = -n;
	}
	while (n > 9)
	{
		count_number++;
		n = n / 10;
	}
	return (count_number + is_neg + 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		is_neg;

	len = ft_nbrlen(n);
	is_neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		is_neg = 1;
		n = -n;
	}
	while (len-- > 0)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	if (is_neg == 1)
		str[0] = '-';
	return (str);
}
/*
int main(void)
{
	printf("%s\n", ft_itoa(100));
	printf("%s\n", ft_itoa(-100));
}
*/
