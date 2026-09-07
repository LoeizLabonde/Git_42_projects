/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:03:58 by kduroux           #+#    #+#             */
/*   Updated: 2025/02/28 10:45:35 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int		ft_touch(float px, float py, t_game *game);
void	ft_get_info_map(t_game *game);
int		check_wall_ori(t_game *game, int x, int y);
void	check_wall_side(t_game *game);

int	ft_touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (y >= 0 && y < game->mapinfo.height && x >= 0 && x < game->mapinfo.width)
	{
		if (game->map[y][x] == 'P')
			return (game->door);
		if (game->map[y][x] == 'l')
			return (game->doorl);
		if (game->map[y][x] == '1')
			return (1);
	}
	else
		ft_close(game);
	return (0);
}

int	ft_coll(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = (int)(px) / BLOCK;
	y = (int)(py) / BLOCK;
	if (y >= 0 && y < game->mapinfo.height && x >= 0 && x < game->mapinfo.width)
	{
		if (game->map[y][x] == 'P')
			return (game->door);
		if (game->map[y][x] == 'l')
			return (game->doorl);
		if (game->map[y][x] == '1')
			return (1);
	}
	else
		ft_close(game);
	return (0);
}

int	ft_touch_event(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = (int)(px) / BLOCK;
	y = (int)(py) / BLOCK;
	if (y >= 0 && y < game->mapinfo.height && x >= 0 && x < game->mapinfo.width)
	{
		if (game->map[y][x] == 'x')
			return (1);
	}
	else
		ft_close(game);
	return (0);
}
