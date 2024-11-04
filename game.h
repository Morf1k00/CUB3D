/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:57:44 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/04 15:08:37 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include "libft/gnl/get_next_line.h"
# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>

//normal working modes:
// # define WIDTH 1260
// # define HEIGHT 800
# define WIDTH 1920 	
# define HEIGHT 1080
// slow working modes:
// # define WIDTH 2560
// # define HEIGHT 1440
// # define WIDTH 3200
// # define HEIGHT 1800
// # define WIDTH 3840 
// # define HEIGHT 2160
# define FOV 60
# define TILE_SIZE 64
# define PLAYER_RADIUS 5
# define M_PI 3.14159265358979323846
# define MAX_DISTANCE 100
# define MOVE_SPEED 0.1
# define ROTATION_SPEED 10

typedef struct s_texture
{
	void	*img;		// Pointer to the image object
	char	*data;		// Pointer to the image data
	int		bpp;		// Bits per pixel
	int		size_line;	// Size of a line of the image in bytes
	int		endian;		// Endianness of the image data
	int		width;		// Width of the image in pixels
	int		height;		// Height of the image in pixels
	char	*path;		// Path to the image file
}			t_texture;

typedef struct s_render
{
	int		texture_step;	/* Stp sz 4 texture mapping, determines how much 
							2 step in the txtre 4 each pixel drawn */
	int		tex_pos;	// Position in the texture
	int		x;	// Current x-coordinate in the rendering process
	int		y; // Current y-coordinate in the rendering process
	float	ray_angle;	// Angle of the current ray
	float	ray_angle_rad;	// Angle of the current ray in radians
	float	ray_dir_x;	// Direction of the ray along the x-axis
	float	ray_dir_y;	// Direction of the ray along the y-axis
	float	delta_dist_x;	// Distance 2 t next x-side in t map frm t crrnt pos
	float	delta_dist_y;	// Distance 2 t next y-side in t map frm t crrnt pos
	int		map_x;	// Current x-coordinate in the map
	int		map_y;	// Current y-coordinate in the map
	float	side_dist_x;	//Distances to the next x-side ...
	float	side_dist_y;	//...y-side in the map from the current position.
	int		step_x;	// Step direction along the x-axis (1 or -1)
	int		step_y;	// Step direction along the y-axis (1 or -1)
	int		side;	// Indicates whether th ray hit a vertical or hrizntl wall
	int		hit;	// Indicates whether a wall was hit (1 if hit, 0 otherwise)
	float	wall_x;	// Exact x-coordinate where the wall was hit
	float	perp_wall_dist;	// Perpendicular distance from the player 2 th wall
	int		wall_height;	// Height of the wall slice to be drawn
	int		draw_start;	// Starting y-coordinate for drawing the wall slice
	int		draw_end;	// Ending y-coordinate for drawing the wall slice
	int		wall_type;	// Type of wall (used for selecting the texture)
	int		tex_y;	// y-coordinate in the texture
	int		tex_x;	// x-coordinate in the texture
	int		color;	// Color of the current pixel
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

/*
 	Refacturing. Structure 2 make less then 5 parameters 4 recursive funtion 
	int f_fill(t_map_data *map_data, int p_y, int p_x) - roi 1101
*/
typedef struct s_map_data
{
	int		height;
	int		width;
	char	**map;
}				t_map_data;

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

// int		ft_strlen(const char *s);
// char	*ft_strdup(const char *src);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	ft_strlcpy(char *dst, const char *src, size_t dstsize);
// char	*ft_strchr(const char *s, int c);
// char	*ft_strjoin(char const *s1, char const *s2);
void	finder_coordinate(t_data *data, char *file_name);
// int		ft_atoi(const char *str);
// char	**ft_split(char const *s, char c);
void	load_textures(t_data *data);
void	ft_raycast(t_data *data);
void	check_map(t_data *data);
int		ft_isspace(char c);
void	map_rewrite(t_data *data);
int		count_tabs(char *line);
bool	isMapClosed(t_data *data, int playerX, int playerY);
void	check_walls(t_data *data);

/* render2.c  refactoring render.c - 1030 roi*/
void	draw_walls(t_data *data, int x, int y);
void	texture_assign(t_data *data);
/*  count_tabs.c	called from map_rewrite.c -	refactured by roi 1103 */
int		count_tabs(char *line);

#endif