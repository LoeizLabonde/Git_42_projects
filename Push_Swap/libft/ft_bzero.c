/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:07:40 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/21 13:38:24 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<aio.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ps;

	i = 0;
	ps = (unsigned char *) s;
	while (i < n)
	{
		ps[i] = 0;
		i++;
	}
}
