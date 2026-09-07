/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:34:19 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/08 11:35:19 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	ft_free_parse(t_game game)
{
	free_tab((void **)game.mapinfo.file);
	ft_free_text(game);
}

void	ft_free_text(t_game game)
{
	free(game.texinfo.north);
	free(game.texinfo.south);
	free(game.texinfo.east);
	free(game.texinfo.west);
}
