/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:17:37 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/11 17:04:37 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	ft_init_all(t_game *game)
{
	if (ft_init_player(game) == -1)
	{
		ft_free_text(*game);
		free_tab((void **)game->map);
		free_tab((void **)game->mapinfo.file);
		return (-1);
	}
	game->img_tab = ft_init_img_tab();
	ft_init_window(game);
	create_images(game);
	ft_draw_background(game);
	ft_render_minimap(game);
	return (0);
}

int	cme(t_game *data, int i, int j)
{
	if (data->map[i][j] == ' ' || data->map[i][j] == '\t'
			|| data->map[i][j] == '\r'
			|| data->map[i][j] == '\v' || data->map[i][j] == '\f')
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac == 2)
	{
		(void) av;
		if (ft_init_texinfo(&game.texinfo) == FAILURE)
			return (FAILURE);
		ft_init_game(&game);
		if (parse_file(av, ac, &game) == FAILURE)
			return (FAILURE);
		if (ft_init_all(&game) == -1)
			return (err_msg(game.mapinfo.path,
					ERR_PLAYER_POS, FAILURE));
		mlx_hook(game.win, 17, 1L << 0, ft_close, &game);
		mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game.player);
		mlx_hook(game.win, 6, 1L << 6, mouse_motion_handler, &game);
		mlx_loop_hook(game.mlx, ft_game_loop, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
