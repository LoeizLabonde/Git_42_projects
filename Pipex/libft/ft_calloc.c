/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:45:22 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/22 15:02:15 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include <limits.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*t;
	size_t	t_size;

	t_size = nmemb * size;
	if (nmemb != 0 && t_size / nmemb != size)
		return (NULL);
	t = malloc(t_size);
	if (!t)
		return (NULL);
	ft_bzero(t, t_size);
	return (t);
}
