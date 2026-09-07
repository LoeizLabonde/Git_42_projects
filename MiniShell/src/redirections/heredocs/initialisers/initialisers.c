/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:23:15 by apetitco          #+#    #+#             */
/*   Updated: 2025/01/24 14:24:38 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_hd_filler(char **line, char **expanded_line, bool *expand_mode)
{
	*line = NULL;
	*expanded_line = NULL;
	*expand_mode = true;
}
