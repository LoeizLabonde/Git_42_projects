/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:29:40 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/11 16:25:07 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

void	ft_init_window(t_game *game);
void	ft_init_null_mlx(t_game *data);
void	ft_free_and_exit(t_game *game);
int		ft_close(t_game *game);

void	ft_init_window(t_game *game)
{
	ft_init_null_mlx(game);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		ft_free_and_exit(game);
	game->win = mlx_new_window(game->mlx,
			WINDOWS_WIDTH, WINDOWS_HEIGHT, "Cub3D");
	if (game->win == NULL)
		ft_free_and_exit(game);
}

void	ft_init_null_mlx(t_game *data)
{
	data->addr = NULL;
	data->mlx = NULL;
	data->win = NULL;
}

void	ft_free_and_exit(t_game *game)
{
	free(game->mlx);
	free(game->addr);
	free(game->win);
	free(game->img_tab[IMG].ptr);
	exit(0);
}

int	ft_close(t_game *game)
{
	int	i;

	i = 0;
	mlx_destroy_window(game->mlx, game->win);
	while (i < IMG_TAB)
		mlx_destroy_image(game->mlx, game->img_tab[i++].ptr);
	mlx_destroy_display(game->mlx);
	free_tab((void **)game->map);
	free_tab((void **)game->mapinfo.file);
	free(game->texinfo.north);
	free(game->texinfo.south);
	free(game->texinfo.east);
	free(game->texinfo.west);
	free(game->img_tab);
	free(game->mlx);
	exit(0);
}
