/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitters_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:59:24 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/30 13:59:28 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

t_error	handle_ro(t_block *nav, int *i)
{
	t_block	*tmp;
	int		j;

	if (*i != 0)
	{
		tmp = block_new(&nav->str[*i]);
		if (!tmp)
			return (ERROR);
		nav->str[*i] = '\0';
		tmp->type = REDIR_O;
		block_add_after(nav, tmp);
		nav = nav->next;
	}
	else
		nav->type = REDIR_O;
	j = 1;
	while (ft_is_ifs(nav->str[j]))
		j++;
	tmp = block_new(&nav->str[j]);
	if (!tmp)
		return (ERROR);
	block_add_after(nav, tmp);
	nav->str[1] = '\0';
	return (NO_ERROR);
}

int	handle_pipe(t_block *nav, int *i)
{
	t_block	*tmp;
	int		j;

	if (*i != 0)
	{
		tmp = block_new(&nav->str[*i]);
		if (!tmp)
			return (ERROR);
		nav->str[*i] = '\0';
		tmp->type = PIPE;
		block_add_after(nav, tmp);
		nav = nav->next;
	}
	else
		nav->type = PIPE;
	j = 1;
	tmp = block_new(&nav->str[j]);
	if (!tmp)
		return (ERROR);
	block_add_after(nav, tmp);
	nav->str[1] = '\0';
	return (NO_ERROR);
}
