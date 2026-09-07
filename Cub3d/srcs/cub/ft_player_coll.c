/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_coll.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:09:04 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/11 14:48:49 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	ft_coll_door(t_game *game, float cos_angle,
			float sin_angle, float speed)
{
	t_player	*player;
	float		tmp_x;
	float		tmp_y;

	player = &game->player;
	tmp_x = player->x;
	tmp_y = player->y;
	tmp_x += (cos_angle * speed) * 10;
	tmp_y += (sin_angle * speed) * 10;
	if (ft_coll(tmp_x, tmp_y, game) == 2)
		game->door = 0;
	else if (ft_coll(tmp_x, tmp_y, game) == 3)
		game->doorl = 0;
	else if (ft_coll(tmp_x, tmp_y, game) == 0)
		game->door = 2;
}

void	ft_coll_up(t_game *game, float cos_angle,
			float sin_angle, float speed)
{
	t_player	*player;
	float		tmp_x;
	float		tmp_y;

	player = &game->player;
	tmp_x = player->x;
	tmp_y = player->y;
	tmp_x += cos_angle * speed;
	tmp_y += sin_angle * speed;
	if (ft_coll(tmp_x, tmp_y, game))
		return ;
	if (ft_touch_event(player->x, player->y, game) == 1)
		game->doorl = 3;
	player->x += cos_angle * speed;
	player->y += sin_angle * speed;
}

void	ft_coll_down(t_game *game, float cos_angle,
			float sin_angle, float speed)
{
	t_player	*player;
	float		tmp_x;
	float		tmp_y;

	player = &game->player;
	tmp_x = player->x;
	tmp_y = player->y;
	tmp_x -= cos_angle * speed;
	tmp_y -= sin_angle * speed;
	if (ft_coll(tmp_x, tmp_y, game))
		return ;
	if (ft_touch_event(player->x, player->y, game) == 1)
		game->doorl = 3;
	player->x -= cos_angle * speed;
	player->y -= sin_angle * speed;
}

void	ft_coll_left(t_game *game, float cos_angle,
			float sin_angle, float speed)
{
	t_player	*player;
	float		tmp_x;
	float		tmp_y;

	player = &game->player;
	tmp_x = player->x;
	tmp_y = player->y;
	tmp_x += sin_angle * speed;
	tmp_y -= cos_angle * speed;
	if (ft_coll(tmp_x, tmp_y, game))
		return ;
	if (ft_touch_event(player->x, player->y, game) == 1)
		game->doorl = 3;
	player->x += sin_angle * speed;
	player->y -= cos_angle * speed;
}

void	ft_coll_right(t_game *game, float cos_angle,
			float sin_angle, float speed)
{
	t_player	*player;
	float		tmp_x;
	float		tmp_y;

	player = &game->player;
	tmp_x = player->x;
	tmp_y = player->y;
	tmp_x -= sin_angle * speed;
	tmp_y += cos_angle * speed;
	if (ft_coll(tmp_x, tmp_y, game))
		return ;
	if (ft_touch_event(player->x, player->y, game) == 1)
		game->doorl = 0;
	player->x -= sin_angle * speed;
	player->y += cos_angle * speed;
}
