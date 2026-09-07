/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:11:31 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/11 15:42:58 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

void	ft_init_game(t_game *game);

int	ft_init_texinfo(t_texinfo *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor_r = 0;
	textures->floor_g = 0;
	textures->floor_b = 0;
	textures->ceiling_r = 0;
	textures->ceiling_g = 0;
	textures->ceiling_b = 0;
	if (TEXW != 64 || TEXH != 64)
		return (1);
	else
		return (0);
}

int	ft_init_player(t_game *game)
{
	if (ft_player_pos(game) == -1)
		return (-1);
	game->player.key_up = 0;
	game->player.key_down = 0;
	game->player.key_right = 0;
	game->player.key_left = 0;
	game->player.key_shift = 0;
	game->player.key_e = 0;
	game->player.left_rotate = 0;
	game->player.right_rotate = 0;
	game->player.minimap = 0;
	return (0);
}

void	ft_init_game(t_game *game)
{
	game->height = WINDOWS_HEIGHT;
	game->width = WINDOWS_WIDTH;
	game->minimap.height = WINDOWS_HEIGHT_MINIMAP;
	game->minimap.width = WINDOWS_WIDTH_MINIMAP;
	game->minimap_size = 0;
	game->dir = 0;
	game->side = 0;
	game->err = 0;
	game->door = 2;
	game->doorl = 3;
	game->att_coef = 0.001;
	game->map = NULL;
}
