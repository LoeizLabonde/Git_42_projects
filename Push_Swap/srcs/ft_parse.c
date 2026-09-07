/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:54:16 by llabonde          #+#    #+#             */
/*   Updated: 2024/07/19 15:59:16 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack	*ft_parse(int ac, char **av)
{
	t_stack	*stack_a;
	int		i;

	i = 1;
	stack_a = NULL;
	if (ac < 2)
		ft_error();
	else if (ac == 2)
		stack_a = ft_parse_args_quoted(av);
	else
		list_args(av, &stack_a);
	return (stack_a);
}
