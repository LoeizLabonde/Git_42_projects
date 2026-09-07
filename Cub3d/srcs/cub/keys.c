/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:03:56 by kduroux           #+#    #+#             */
/*   Updated: 2025/02/26 10:04:34 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int		ft_key_press(int keycode, t_game *game);
int		ft_key_release(int keycode, t_player *player);
void	wrap_mouse_position(t_game *game, int x, int y);
int		mouse_motion_handler(int x, int y, t_game *game);

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = 1;
	if (keycode == S)
		game->player.key_down = 1;
	if (keycode == A)
		game->player.key_left = 1;
	if (keycode == D)
		game->player.key_right = 1;
	if (keycode == 101)
		game->player.key_e = 1;
	if (keycode == LEFT)
		game->player.left_rotate = 1;
	if (keycode == RIGHT)
		game->player.right_rotate = 1;
	if (keycode == 65505)
		game->player.key_shift = 1;
	if (keycode == 65307)
		ft_close(game);
	if (keycode == 109)
		game->player.minimap = 1;
	return (0);
}

int	ft_key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = 0;
	if (keycode == S)
		player->key_down = 0;
	if (keycode == A)
		player->key_left = 0;
	if (keycode == D)
		player->key_right = 0;
	if (keycode == 101)
		player->key_e = 0;
	if (keycode == LEFT)
		player->left_rotate = 0;
	if (keycode == RIGHT)
		player->right_rotate = 0;
	if (keycode == 65505)
		player->key_shift = 0;
	if (keycode == 109)
		player->minimap = 0;
	return (0);
}

void	wrap_mouse_position(t_game *game, int x, int y)
{
	(void)y;
	if (x > WINDOWS_WIDTH - 20)
	{
		x = 20;
		mlx_mouse_move(game->mlx, game->win,
			WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2);
	}
	if (x < 20)
	{
		x = WINDOWS_WIDTH - 20;
		mlx_mouse_move(game->mlx, game->win,
			WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2);
	}
}

int	mouse_motion_handler(int x, int y, t_game *game)
{
	static int	old_x = WINDOWS_WIDTH / 2;

	wrap_mouse_position(game, x, y);
	if (x == old_x)
		return (0);
	else if (x < old_x)
		game->player.angle -= 0.03;
	else if (x > old_x)
		game->player.angle += 0.03;
	old_x = x;
	return (0);
}
