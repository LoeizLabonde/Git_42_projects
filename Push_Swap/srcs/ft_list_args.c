/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:51:03 by llabonde          #+#    #+#             */
/*   Updated: 2024/07/19 15:59:18 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	list_args(char **av, t_stack **stack_a)
{
	long	i;

	i = 1;
	while (av[i] != NULL)
	{
		ft_add_back(stack_a, ft_stack_new(ft_atoi(av[i])));
		i++;
	}
}
