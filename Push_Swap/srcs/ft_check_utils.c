/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:43:23 by llabonde          #+#    #+#             */
/*   Updated: 2024/07/19 15:59:22 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	sign(int c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

int	digit(int c)
{
	if ((c >= 48) && (c <= 57))
		return (1);
	return (0);
}

int	space(int c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	check_error(char **av, int i, int j)
{
	while (av[i])
	{
		j = 0;
		while ((av[i][j] != '\0'))
		{
			if (sign(av[i][j]))
			{
				j++;
				if (!digit(av[i][j]))
					return (false);
			}
			else if (digit(av[i][j]))
			{
				j++;
				if (av[i][j] == '\0')
					break ;
				if (!digit(av[i][j]) && !space(av[i][j]))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
