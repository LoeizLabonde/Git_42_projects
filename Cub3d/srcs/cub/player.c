/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:29:01 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/08 16:15:11 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	ft_move_player(t_game *game);

void	ft_set_up_pos(t_game *game, char **map, int x, int y)
{
	game->player.x = x * BLOCK;
	game->player.y = y * BLOCK;
	if (map[y][x] == 'N')
		game->player.angle = M_PI * 1.5;
	else if (map[y][x] == 'S')
		game->player.angle = M_PI / 2;
	else if (map[y][x] == 'E')
		game->player.angle = M_PI * 2;
	else if (map[y][x] == 'W')
		game->player.angle = M_PI;
}

int	ft_player_pos(t_game *game)
{
	char	**map;
	int		x;
	int		y;

	map = game->map;
	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				ft_set_up_pos(game, map, x, y);
				return (0);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (-1);
}

void	ft_move_player_wasd(t_game	*game, float cos_angle,
			float sin_angle, float speed)
{
	t_player	*player;

	player = &game->player;
	if (player->key_up)
		ft_coll_up(game, cos_angle, sin_angle, speed);
	if (player->key_down)
		ft_coll_down(game, cos_angle, sin_angle, speed);
	if (player->key_left)
		ft_coll_left(game, cos_angle, sin_angle, speed);
	if (player->key_right)
		ft_coll_right(game, cos_angle, sin_angle, speed);
	if (player->key_e)
		ft_coll_door(game, cos_angle, sin_angle, speed);
}

void	ft_move_player(t_game *game)
{
	int			speed;
	float		angle_speed;
	float		cos_angle;
	float		sin_angle;
	t_player	*player;

	speed = 3;
	angle_speed = 0.025;
	player = &game->player;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * M_PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * M_PI;
	if (player->key_shift)
		speed = 10;
	ft_move_player_wasd(game, cos_angle, sin_angle, speed);
}
