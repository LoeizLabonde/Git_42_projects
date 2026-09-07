/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitters_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:08:00 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/30 13:59:59 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

t_error	handle_ap(t_block *nav, int *i)
{
	t_block	*tmp;
	int		j;

	if (*i != 0)
	{
		tmp = block_new(&nav->str[*i]);
		if (!tmp)
			return (ERROR);
		nav->str[*i] = '\0';
		tmp->type = APPEND;
		block_add_after(nav, tmp);
		nav = nav->next;
	}
	else
		nav->type = APPEND;
	j = 2;
	while (ft_is_ifs(nav->str[j]))
		j++;
	tmp = block_new(&nav->str[j]);
	if (!tmp)
		return (ERROR);
	block_add_after(nav, tmp);
	nav->str[2] = '\0';
	return (NO_ERROR);
}

t_error	handle_hd(t_block *nav, int *i)
{
	t_block	*tmp;
	int		j;

	if (*i != 0)
	{
		tmp = block_new(&nav->str[*i]);
		if (!tmp)
			return (ERROR);
		nav->str[*i] = '\0';
		tmp->type = HEREDOC;
		block_add_after(nav, tmp);
		nav = nav->next;
	}
	else
		nav->type = HEREDOC;
	j = 2;
	while (ft_is_ifs(nav->str[j]))
		j++;
	tmp = block_new(&nav->str[j]);
	if (!tmp)
		return (ERROR);
	block_add_after(nav, tmp);
	nav->str[2] = '\0';
	return (NO_ERROR);
}

t_error	handle_ifs(t_block *nav, int *i)
{
	t_block	*tmp;

	nav->str[*i] = '\0';
	(*i)++;
	while (nav->str[*i] && ft_is_ifs(nav->str[*i]))
		(*i)++;
	tmp = block_new(&nav->str[*i]);
	if (!tmp)
		return (ERROR);
	tmp->type = RAW;
	block_add_after(nav, tmp);
	nav->str[*i] = '\0';
	return (NO_ERROR);
}

int	handle_ri(t_block *nav, int *i)
{
	t_block	*tmp;
	int		j;

	if (*i != 0)
	{
		tmp = block_new(&nav->str[*i]);
		if (!tmp)
			return (ERROR);
		nav->str[*i] = '\0';
		tmp->type = REDIR_I;
		block_add_after(nav, tmp);
		nav = nav->next;
	}
	else
		nav->type = REDIR_I;
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
