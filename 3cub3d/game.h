/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:57:44 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/08 16:51:18 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1260
# define HEIGHT 800
# define FOV 60
# define MAP_WIDTH 5
# define MAP_HEIGHT 5
# define TILE_SIZE 64
# define PLAYER_RADIUS 5
# define M_PI 3.14159265358979323846
# define FLOOR_COLOR 0x000000
# define MAX_DISTANCE 100
# define MOVE_SPEED 0.1
# define ROTATION_SPEED 10

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}			t_texture;

typedef struct s_render
{
	int		x;
	int		y;
	float	ray_angle;
	float	ray_angle_rad;
	float	ray_dir_x;
	float	ray_dir_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	float	perp_wall_dist;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		tex_y;
	int		tex_x;
	int		color;
}			t_render;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	float		player_angle;
	float		player_x; // Центр тайла
	float		player_y;
	int			map[MAP_HEIGHT][MAP_WIDTH];
	t_texture	wall_texture;
	t_texture	floor_texture;
	t_render	render;
}				t_data;

void	load_texture(t_data *data, t_texture *texture, const char *file_path);
void	clear_screen(t_data *data, int color);
void	render(t_data *data);
int		handle_key_press(int keycode, t_data *data);
int		game_loop(t_data *data);
int		move_a(t_data *data);
int		move_d(t_data *data);
int		move_w(t_data *data);
int		move_s(t_data *data);

#endif