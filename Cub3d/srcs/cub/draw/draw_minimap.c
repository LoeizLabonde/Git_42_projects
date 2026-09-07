/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:23:30 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/11 17:15:17 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

void	ft_draw_player_on_minimap(t_game *game)
{
	int	player_x;
	int	player_y;
	int	tile_size;
	int	i;
	int	j;

	tile_size = WINDOWS_WIDTH / game->mapinfo.width;
	player_x = (int)(game->player.x / tile_size);
	player_y = (int)(game->player.y / tile_size);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			ft_put_pixel_on_img(&game->img_tab[IMG],
				player_x + i, player_y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	ft_draw_minimap(t_game *game)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;
	int	tile_size;

	tile_size = WINDOWS_WIDTH_MINIMAP / game->mapinfo.width;
	x = 0;
	while (x++ < WINDOWS_WIDTH_MINIMAP)
	{
		y = 0;
		while (y++ < WINDOWS_HEIGHT_MINIMAP)
		{
			map_x = x / tile_size;
			map_y = y / tile_size;
			if (map_x < game->mapinfo.width && map_y < game->mapinfo.height)
			{
				if (game->map[map_y][map_x] == '1')
					ft_put_pixel_on_img(&game->img_tab[IMG], x, y, 0x000000);
				else
					ft_put_pixel_on_img(&game->img_tab[IMG], x, y, 0xFFFFFF);
			}
		}
	}
}

void	ft_render_minimap(t_game *game)
{
	ft_draw_minimap(game);
	ft_draw_player_on_minimap(game);
}
