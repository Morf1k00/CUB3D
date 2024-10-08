/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:52:52 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/08 15:14:38 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define WIDTH 1260
#define HEIGHT 800
#define FOV 60
#define MAP_WIDTH 5
#define MAP_HEIGHT 5
#define TILE_SIZE 64
#define PLAYER_RADIUS 5
#define M_PI 3.14159265358979323846
#define FLOOR_COLOR 0x000000
#define MAX_DISTANCE 100
#define MOVE_SPEED 0.1
#define ROTATION_SPEED 3

typedef struct {
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
    int width;   // Ширина текстуры
    int height;  // Высота текстуры
	
} t_texture;
// Структура для текстуры
typedef struct {
    void *mlx;
    void *win;
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
	float player_angle;
	float player_x; // Центр тайла
	float player_y;
	int map[MAP_HEIGHT][MAP_WIDTH];  
	t_texture wall_texture; // Текстура для стен
	t_texture floor_texture; // Текстура для пола
} t_data;

// Структура для текстуры


// Function Prototypes
void load_texture(t_data *data, t_texture *texture, const char *file_path);
void clear_screen(t_data *data, int color);
void render(t_data *data);
int handle_key_press(int keycode, t_data *data);
int game_loop(t_data *data);
int	move_a(t_data *data);
int	move_d(t_data *data);
int	move_w(t_data *data);
int	move_s(t_data *data);

#endif
