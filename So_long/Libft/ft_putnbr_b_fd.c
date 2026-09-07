/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_b_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:57:18 by llabonde          #+#    #+#             */
/*   Updated: 2024/08/19 17:05:16 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_b_fd(unsigned long int nbr, char *base, int fd)
{
	size_t		base_len;
	int			rt_value;
	int			temp;

	base_len = ft_strlen(base);
	rt_value = 0;
	temp = 0;
	if (nbr >= base_len)
	{
		ft_putnbr_b_fd(nbr / base_len, base, fd);
		ft_putnbr_b_fd(nbr % base_len, base, fd);
	}
	else
	{
		temp = ft_putchar_fd(base[nbr], fd);
		if (temp == -1)
			return (temp);
	}
	while (nbr >= base_len)
	{
		nbr /= base_len;
		rt_value++;
	}
	return (++rt_value);
}
