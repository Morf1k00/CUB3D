/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:57:44 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/25 13:34:17 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>

# define WIDTH 1920
# define HEIGHT 1260
# define FOV 60
# define TILE_SIZE 64
# define PLAYER_RADIUS 5
# define M_PI 3.14159265358979323846
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
	char	*path;
}			t_texture;

typedef struct s_render
{
	int 	texture_step;
	int 	tex_pos;
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
	float	wall_x;
	float	perp_wall_dist;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		wall_type;
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
	float		player_x;
	float		player_y;
	char		**map;
	int			map_width;
	int			map_height;
	t_texture	wall_texture[4];
	int			color_f;	
	int			color_c;
	t_render	render;
}				t_data;

void	clear_screen(t_data *data);
int		handle_key_press(int keycode, t_data *data);
int		game_loop(t_data *data);
int		move_a(t_data *data);
int		move_d(t_data *data);
int		move_w(t_data *data);
int		move_s(t_data *data);
char	*get_next_line(int fd);
void	open_file(char *map_path, t_data *dat);
void	maps_checker(t_data *dat);
void	player_position(t_data *dat);

int		ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	finder_coordinate(t_data *data, char *file_name);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
void	load_textures(t_data *data);
void	ft_raycast(t_data *data);
void	check_map(t_data *data);
int		ft_isspace(char c);
void map_rewrite(t_data *data);
int count_tabs(char *line);
bool isMapClosed(t_data *data, int playerX, int playerY);
void check_walls(t_data *data);

#endif