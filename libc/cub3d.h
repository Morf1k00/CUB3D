/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:32:49 by rkrechun          #+#    #+#             */
/*   Updated: 2024/09/04 14:07:30 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct s_ray
{
    double player_x;       // Позиция игрока по оси X
    double player_y;       // Позиция игрока по оси Y
    double dir_x;          // Направление взгляда игрока по оси X
    double dir_y;          // Направление взгляда игрока по оси Y
    double plane_x;        // Вектор камеры по оси X (перпендикулярный направлению взгляда)
    double plane_y;        // Вектор камеры по оси Y (перпендикулярный направлению взгляда)
    double ray_dir_x;      // Направление луча по оси X (определяется для каждого столбца экрана)
    double ray_dir_y;      // Направление луча по оси Y (определяется для каждого столбца экрана)
    double side_dist_x;    // Расстояние от текущей позиции игрока до первой стороны по X, пересекаемой лучом
    double side_dist_y;    // Расстояние от текущей позиции игрока до первой стороны по Y, пересекаемой лучом
    double delta_dist_x;   // Расстояние, которое луч должен пройти по оси X, чтобы пересечь линию сетки (константа для данного направления луча)
    double delta_dist_y;   // Расстояние, которое луч должен пройти по оси Y, чтобы пересечь линию сетки (константа для данного направления луча)
    double perp_wall_dist; // Перпендикулярное расстояние от игрока до пересеченной стены (для коррекции эффекта "рыбьего глаза")
    int map_x;             // Координата текущего квадрата карты по оси X (в какой клетке находится луч)
    int map_y;             // Координата текущего квадрата карты по оси Y (в какой клетке находится луч)
    int step_x;            // Направление шага по оси X (в каком направлении луч движется по оси X: +1 или -1)
    int step_y;            // Направление шага по оси Y (в каком направлении луч движется по оси Y: +1 или -1)
    int side;              // Какая стена была пересечена: 0 - по оси X, 1 - по оси Y
} t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map2d;
	int		map_width;
	int		map_height;
	
	int		key_press;
	void	*floor;
	void 	*wall;
	t_ray	*ray;
}				t_game;

char	*get_next_line(int fd);
void open_file(char *map_path, t_game *dat);
void player_position(t_game *dat);
void	*ft_calloc(size_t count, size_t size);
char ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
int ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void maps_checker(t_game *dat);
void image_in_map(t_game *game);
void	ft_bzero(void *s, size_t n);
void map_paint(t_game *dat);
// void raycasting(t_game *game);
int raycasting(void *param);

#endif
