/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:57:44 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/30 11:26:26 by oruban           ###   ########.fr       */
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

# define WIDTH 1260
# define HEIGHT 800
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
	int		texture_step;
	int		tex_pos;
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

/* 
	 data structure that holds all the necessary information for the game's
	 state and rendering. - roi 1030
 */
typedef struct s_data
{
	void		*mlx;	// Pointer to the MLX instance (MiniLibX library)
	void		*win;	// Pointer to the window instance created by MLX
	void		*img;	// Pointer to the image instance created by MLX
	char		*data;	// Pointer to the image data
	int			bpp;	// Bits per pixel (color depth of the image)	
	int			size_line;	// Size of a line of pixels in bytes
	int			endian;	// Endianness of the image data
	float		player_angle;	// Angle of the player's view direction
	float		player_x;	// Player's x-coordinate in the game world
	float		player_y;	// Player's y-coordinate in the game world
	char		**map;		// 2D array representing the game map
	int			map_width;	// Width of the game map
	int			map_height;	// Height of the game map
	t_texture	wall_texture[4]; // Array of textures for the walls (N, S, W, E)
	int			color_f;	//color of floor
	int			color_c;	//color of ceiling
	t_render	render;		// Structure holding rendering-related data	
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
void	map_rewrite(t_data *data);
int		count_tabs(char *line);
bool	isMapClosed(t_data *data, int playerX, int playerY);
void	check_walls(t_data *data);

#endif