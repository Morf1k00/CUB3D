/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:55:12 by rkrechun          #+#    #+#             */
/*   Updated: 2024/09/11 14:21:09 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef CUB3D_H
// #include "mlx/mlx.h"
// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>

// #define WIDTH 1260         // Ширина окна в пикселях
// #define HEIGHT 800        // Высота окна в пикселях
// #define FOV 60            // Поле зрения (угол обзора) в градусах
// #define MAP_WIDTH 5       // Ширина карты в тайлах
// #define MAP_HEIGHT 5      // Высота карты в тайлах
// #define TILE_SIZE 64     // Размер одного тайла в пикселях
// #define PLAYER_RADIUS 5  // Радиус игрока в пикселях
// #define M_PI 3.14159265358979323846 // Значение числа π (пи)
// #define FLOOR_COLOR 0x000000
// #define MAX_DISTANCE 100 // Максимальное расстояние для прорисовки
// #define MOVE_SPEED 0.1  // Скорость движения игрока
// #define ROTATION_SPEED 3  // Скорость поворота в градусах

// // Упрощенная карта (1 = стена, 0 = пустое место)
// // int map[MAP_HEIGHT][MAP_WIDTH] = {
// //     {1, 1, 1, 1, 1},
// //     {1, 0, 0, 0, 1},
// //     {1, 0, 1, 0, 1},
// //     {1, 0, 1, 0, 1},
// //     {1, 1, 1, 1, 1}
// // };

// // Позиция игрока
// float player_x = 2.5; // Центр тайла
// float player_y = 1.5; // Центр тайла
// float player_angle = 90; // Угол направления игрока

// // // Структура для данных MLX
// typedef struct {
//     void *mlx;
//     void *win;
//     void *img;
//     char *data;
//     int bpp;
//     int size_line;
//     int endian;
// } t_data;

// // Структура для текстуры
// typedef struct {
//     void *img;
//     char *data;
//     int bpp;
//     int size_line;
//     int endian;
//     int width;   // Ширина текстуры
//     int height;  // Высота текстуры
// 	t_texture wall_texture; // Текстура для стен
// 	t_texture floor_texture; // Текстура для пола
// } t_texture;

// typedef struct {
//     float x;
//     float y;
//     float angle;
// } t_player;

// typedef struct {
//     int width;
//     int height;
//     int map[MAP_HEIGHT][MAP_WIDTH];
// } t_map;

// typedef struct {
//     t_data *mlx_data;
//     t_texture *wall_texture;
//     t_player *player;
//     t_map *map;
// } t_game;


// int handle_key_press(int keycode, t_data *data);
// void render(t_data *data);
// void clear_screen(t_data *data, int color);
// void load_texture(t_data *data, t_texture *texture, const char *file_path);
// void handle_input(int keycode, t_game *game);


// #endif

#ifndef CUB3D_H
#define CUB3D_H

// Include necessary libraries
#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

// Define constants
#define WIDTH 1260         // Window width in pixels
#define HEIGHT 800         // Window height in pixels
#define FOV 60             // Field of view in degrees
#define MAP_WIDTH 5        // Map width in tiles
#define MAP_HEIGHT 5       // Map height in tiles
#define TILE_SIZE 64       // Size of each tile in pixels
#define PLAYER_RADIUS 5    // Player radius in pixels
#define M_PI 3.14159265358979323846 // Value of π
#define FLOOR_COLOR 0x000000
#define MAX_DISTANCE 100   // Maximum distance for raycasting
#define MOVE_SPEED 0.1     // Player movement speed
#define ROTATION_SPEED 3   // Player rotation speed

// Structure for player data
typedef struct {
    float x;
    float y;
    float angle;
} t_player;

// Structure for the game map
typedef struct {
    int width;
    int height;
    int map[MAP_HEIGHT][MAP_WIDTH];
} t_map;

// Structure for texture data
typedef struct {
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
    int width;   // Texture width
    int height;  // Texture height
} t_texture;

// Structure for the MLX environment
typedef struct {
    void *mlx;
    void *win;
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
} t_data;

// Structure for the game, bundling all components
typedef struct {
    t_data *mlx_data;
    t_texture *wall_texture;
    t_player *player;
    t_map *map;
} t_game;

// Function prototypes

// Texture loading function
void load_texture(t_data *data, t_texture *texture, const char *file_path);

// Screen clear function
void clear_screen(t_data *data, int color);

// Input handling (player movement and rotation)
int handle_input(int keycode, t_game *game);

// Calculate ray direction
void calculate_ray_direction(float ray_angle, float *ray_dir_x, float *ray_dir_y);

// Raycasting (DDA algorithm)
float perform_dda(float ray_dir_x, float ray_dir_y, t_game *game, int *side);

// Wall rendering function
void draw_wall(int x, int wall_height, int side, t_game *game);

// Render the game scene
void render(t_game *game);

// Main game loop function
int game_loop(t_game *game);

#endif
