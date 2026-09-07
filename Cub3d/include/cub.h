/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:21:24 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/21 13:19:52 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "/home/kduroux/sgoinfre/minilibx-linux/mlx.h"
//# include "/home/llabonde/sgoinfre/minilibx-linux/mlx.h"
//# include "/home/vboxuser/minilib/minilibx-linux/mlx.h"
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

# define DEBUG 0
# define MONSTRE 0
# define MINIMAP 0
# define BLOCK 128
# define TEXW 64
# define TEXH 64
# define IMG_TAB 8

# define WINDOWS_WIDTH  1000
# define WINDOWS_HEIGHT  800

# define WINDOWS_WIDTH_MINIMAP  300
# define WINDOWS_HEIGHT_MINIMAP  200

# define NO 5
# define SO 2
# define WE 3
# define EA 4
# define MM 7
# define DOOR 6
# define BG 1
# define IMG 0

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
}	t_texinfo;

typedef struct s_calc
{
	float	dist;
	float	height;
	int		start_y;
	int		end;
	float	step;
	float	tex_y;
	int		color;
	int		tex_x_coord;
	float	distance_fc;
	float	attenuation;

}	t_calc;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
	float		x;
	float		y;
}	t_mapinfo;

typedef struct s_player
{
	float	x;
	float	y;
	float	teleinx;
	float	teleiny;
	float	teleoutx;
	float	teleouty;
	float	mx;
	float	my;
	float	angle;

	int		key_up;
	int		key_down;
	int		key_right;
	int		key_left;
	int		key_shift;
	int		key_e;

	int		left_rotate;
	int		right_rotate;

	int		minimap;
}	t_player;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		width;
	int		height;
	int		bits_pp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_ray
{
	float	ray_x;
	float	ray_y;
	float	ray_dir_x;
	float	ray_dir_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;

}	t_ray;

typedef struct s_minimap
{
	char		**map;
	int			width;
	int			height;

}	t_minimap;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	char		*addr;
	char		*dst;
	int			bits_pp;
	int			size_line;
	int			endian;
	int			**texture_pixels;
	int			**textures;
	int			width;
	int			height;
	float		att_coef;
	float		minimap_size;
	int			dir;
	int			side;
	int			err;
	int			door;
	int			doorl;
	t_player	player;
	t_mapinfo	mapinfo;
	t_texinfo	texinfo;
	t_minimap	minimap;
	t_calc		calc;
	t_ray		ray;
	t_img		*img_tab;
}	t_game;

// ERROR MESSAGES
# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"

# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not an .xpm file"
# define ERR_FILE_IS_DIR "Is a directory"
# define ERR_FLOOR_CEILING "Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR "Invalid floor RGB color"
# define ERR_COLOR_CEILING "Invalid ceiling RGB color"
# define ERR_INVALID_MAP "Map description is either wrong or incomplete"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_NUM_PLAYER "Map has more than one player"
# define ERR_TEX_RGB_VAL "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING "Missing texture(s)"
# define ERR_TEX_INVALID "Invalid texture(s)"
# define ERR_COLOR_MISSING "Missing color(s)"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_TOO_SMALL "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS "Map is not surrounded by walls"
# define ERR_MAP_LAST "Map is not the last element in file"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_PLAYER_DIR "Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"

//init_window.c
void	ft_init_window(t_game *game);
void	ft_init_null_mlx(t_game *data);
void	ft_free_and_exit(t_game *game);
int		ft_close(t_game *game);

//init_minimap
void	ft_init_minimap(t_minimap *game);
void	ft_init_null_mlx_minimap(t_minimap *data);
void	ft_free_and_exit_minimap(t_minimap *game);

//init.c
int		ft_init_player(t_game *game);
int		ft_init_texinfo(t_texinfo *textures);
void	ft_init_game(t_game *game);

//init_ray->c
void	ft_init_ray(t_ray *ray, t_game *game, float angle);
void	ft_init_ray_null(t_ray *ray);

//init_img.c
t_img	ft_init_img(void);
t_img	*ft_init_img_tab(void);

//create_images.c
void	set_img_addr(t_img *img);
void	create_img(t_game *data, t_img *img, char *filename);
void	create_images(t_game *data);

//utils.c
int		check_texture_validity(t_game *data, t_texinfo texinfo);
int		*check_texture_validity_utils(t_texinfo texinfo, int *fd);
int		parse_file(char **av, int ac, t_game *data);
int		err_msg(char *detail, char *str, int code);
void	free_tab(void **tab);

//player.c
void	ft_move_player(t_game *game);
void	ft_teleport(t_game *game);
int		ft_player_pos(t_game *game);

//keys.c
int		ft_key_release(int keys, t_player *player);
int		ft_key_press(int keycode, t_game *game);
int		mouse_motion_handler(int x, int y, t_game *game);
void	wrap_mouse_position(t_game *game, int x, int y);

//draw.c
void	ft_put_pixel_on_img(t_img *img, int x, int y, int color);
void	ft_draw_background(t_game *game);
int		ft_get_texture(int i, int start_y, t_img *img);
int		tex_x(float ray_x, float ray_y, int side);

//ft_draw_ray.c
void	ft_draw_ray(t_game *game, float start_x, int i);
void	ft_set_dir(t_game *game, t_ray *ray);
void	ft_raycast(t_game *game, t_ray *ray, int i);

//draw_minimap.c
void	ft_draw_wall(int x, int y, int color, t_game *game);
void	ft_draw_player(int x, int y, int color, t_game *game);
void	ft_put_pixel_minimap(t_game *data, int y, int x);
void	render_minimap(t_game *data);

//game.c
int		ft_game_loop(t_game *game);
void	ft_clear(t_game *game);
float	distance(float x, float y);
float	fixed_dist(float x2, float y2, t_game *game);

//map.c
int		ft_coll(float px, float py, t_game *game);
int		ft_touch(float px, float py, t_game *game);
void	ft_get_info_map(t_game *game);
void	check_wall_side(t_game *game);

//texture.c
int		rgbtohex(int r, int g, int b);
int		test(t_game *game, char *filename);

//parsing.c
int		parse_file(char **av, int ac, t_game *file);
int		check_file(char *path);
int		is_dir(char *path);
int		check_file(char *av);
int		is_cubfile(char *path);

//ft_player_coll.c
void	ft_coll_up(t_game *game, float cos_angle,
			float sin_angle, float speed);
void	ft_coll_down(t_game *game, float cos_angle,
			float sin_angle, float speed);
void	ft_coll_right(t_game *game, float cos_angle,
			float sin_angle, float speed);
void	ft_coll_left(t_game *game, float cos_angle,
			float sin_angle, float speed);
void	ft_coll_door(t_game *game, float cos_angle,
			float sin_angle, float speed);

//free.c
void	ft_free_text(t_game game);
void	ft_free_parse(t_game game);

//to be sorted
int		check_end_of_file(t_game *data);
int		check_integrity(char **map_tab, int i, int j);
void	ft_close_fd(int *fd);
int		open_fd(int i, int *fd, char *file);
void	ft_render_minimap(t_game *game);
void	ft_draw_minimap(t_game *game);
void	ft_draw_floor_and_ceiling(t_game *game, int i);
int		ft_touch_event(float px, float py, t_game *game);
void	ft_block1(t_game *game, t_ray *ray, int i);
int		cme(t_game *data, int i, int j);
size_t	find_biggest_len(t_mapinfo *map, int i);
int		get_file_data(t_game *data, char **map);
int		err_msg(char *detail, char *str, int code);
void	free_tab(void **tab);
int		fill_color_textures(t_game *data, t_texinfo *textures,
			char *line, int j);
int		create_map(t_game *data, char **file, int i);
int		parse_data(char *path, t_game *data);
int		check_map_sides(t_mapinfo *map, char **map_tab);
int		check_map_validity(t_game *data, char **map_tab);
#endif
