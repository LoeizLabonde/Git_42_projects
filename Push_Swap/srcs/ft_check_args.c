/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:34:19 by llabonde          #+#    #+#             */
/*   Updated: 2024/07/19 15:59:25 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_isalpha(int c)
{
	if ((c >= 58 && c <= 126) || (c >= 33 && c <= 42)
		|| (c == 44) || (c == 46) || (c == 47))
		return (1);
	return (0);
}

void	alpha_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while ((av[i][j]) != '\0')
		{
			if (ft_isalpha(av[i][j]))
				ft_error();
			j++;
		}
		i++;
	}
}

int	check_args(char **av)
{
	alpha_check(av);
	if (!check_error (av, 1, 0))
		return (false);
	return (true);
}
