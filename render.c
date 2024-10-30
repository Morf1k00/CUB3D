/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:10:39 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/30 12:59:04 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/* 
	Determines which texture to use for the wall and calculates the texture 
	coordinates. - roi 1030

	void	texture_assign(t_data *data)
{
	double	wall_hit;

	// Выбор текстуры в зависимости от стороны
	if (data->render.side == 0) // По оси X (восток или запад)
	{
		if (data->render.step_x > 0)
			data->render.wall_type = 0; // Восток
		else
			data->render.wall_type = 1; // Запад
		wall_hit = data->player_y + data->render.perp_wall_dist
			* data->render.ray_dir_y;
	}
	else // По оси Y (север или юг)
	{
		if (data->render.step_y > 0)
			data->render.wall_type = 2; // Север
		else
			data->render.wall_type = 3; // Юг
		wall_hit = data->player_x + data->render.perp_wall_dist
			* data->render.ray_dir_x;
	}
	// Сдвиг для корректного отображения текстуры
	wall_hit -= floor(wall_hit);
	data->render.tex_x = (int)(wall_hit
			* (double)data->wall_texture[data->render.wall_type].width);
	// Обработка возможных ошибок с координатами текстуры
	if (data->render.tex_x < 0 || data->render.tex_x
		>= data->wall_texture[data->render.wall_type].width)
		data->render.tex_x = 0;
}
 */
void	texture_assign(t_data *data)
{
	double	wall_hit;

	if (data->render.side == 0)
	{
		if (data->render.step_x > 0)
			data->render.wall_type = 0;
		else
			data->render.wall_type = 1;
		wall_hit = data->player_y + data->render.perp_wall_dist
			* data->render.ray_dir_y;
	}
	else
	{
		if (data->render.step_y > 0)
			data->render.wall_type = 2;
		else
			data->render.wall_type = 3;
		wall_hit = data->player_x + data->render.perp_wall_dist
			* data->render.ray_dir_x;
	}
	wall_hit -= floor(wall_hit);
	data->render.tex_x = (int)(wall_hit
			* (double)data->wall_texture[data->render.wall_type].width);
	if (data->render.tex_x < 0 || data->render.tex_x
		>= data->wall_texture[data->render.wall_type].width)
		data->render.tex_x = 0;
}

/* 
	 Determines the step direction and initial side distance for 
	 the ray. - roi 1030
	 28 lines
 */
void	step_determination(t_data *data)
{
	if (data->render.ray_dir_x < 0)
	{
		data->render.step_x = -1;
		data->render.side_dist_x = (data->player_x - data->render.map_x)
			* data->render.delta_dist_x;
	}
	else
	{
		data->render.step_x = 1;
		data->render.side_dist_x = (data->render.map_x + 1.0 - data->player_x)
			* data->render.delta_dist_x;
	}
	if (data->render.ray_dir_y < 0)
	{
		data->render.step_y = -1;
		data->render.side_dist_y = (data->player_y - data->render.map_y)
			* data->render.delta_dist_y;
	}
	else
	{
		data->render.step_y = 1;
		data->render.side_dist_y = (data->render.map_y + 1.0 - data->player_y)
			* data->render.delta_dist_y;
	}
}

/* 
Calculates the direction of the ray for the current vertical stripe. 1030 - roi
 */
// Рассчет угла луча
void	raydir_calculation(t_data *data, int x)
{
	data->render.ray_angle = data->player_angle
		- (FOV / 2.0) + (x * (FOV / (float)WIDTH));
	data->render.ray_angle_rad = data->render.ray_angle * M_PI / 180.0;
	data->render.ray_dir_x = cos(data->render.ray_angle_rad);
	data->render.ray_dir_y = sin(data->render.ray_angle_rad);
	data->render.delta_dist_x = fabs(1 / data->render.ray_dir_x);
	data->render.delta_dist_y = fabs(1 / data->render.ray_dir_y);
	data->render.map_x = (int)data->player_x;
	data->render.map_y = (int)data->player_y;
	data->render.hit = 0;
}

/* 
	Performs the Digital Differential Analysis (DDA) algorithm to find where
	 the ray hits a wall. - roi 1030
 */
void	wallhit_detection(t_data *data)
{
	data->render.hit = 0;
	while (!data->render.hit)
	{
		if (data->render.side_dist_x < data->render.side_dist_y)
		{
			data->render.side_dist_x += data->render.delta_dist_x;
			data->render.map_x += data->render.step_x;
			data->render.side = 0;
		}
		else
		{
			data->render.side_dist_y += data->render.delta_dist_y;
			data->render.map_y += data->render.step_y;
			data->render.side = 1;
		}
		if (data->render.map_x < 0 || data->render.map_x >= data->map_width
			|| data->render.map_y < 0 || data->render.map_y >= data->map_height)
			break ;
		if (data->map[data->render.map_y][data->render.map_x] == '1')
			data->render.hit = 1;
	}
}

/* 
	Calculates the distance to the wall and the height of the wall slice 
	to be drawn. - roi 1030
 */
void	draw_calculation(t_data *data)
{
	if (data->render.side == 0)
		data->render.perp_wall_dist = (data->render.map_x - data->player_x
				+ (1 - data->render.step_x) / 2) / data->render.ray_dir_x;
	else
		data->render.perp_wall_dist = (data->render.map_y - data->player_y
				+ (1 - data->render.step_y) / 2) / data->render.ray_dir_y;
	if (data->render.perp_wall_dist > MAX_DISTANCE)
		data->render.perp_wall_dist = MAX_DISTANCE;
	data->render.wall_height = (int)(HEIGHT / data->render.perp_wall_dist);
	data->render.draw_start = -(data->render.wall_height) / 2 + HEIGHT / 2;
	if (data->render.draw_start < 0)
		data->render.draw_start = 0;
	data->render.draw_end = data->render.wall_height / 2 + HEIGHT / 2;
	if (data->render.draw_end >= HEIGHT)
		data->render.draw_end = HEIGHT - 1;
}

void	draw_walls(t_data *data, int x, int y)
{
	// Вычисление текстурной координаты Y
	data->render.tex_y = (y - data->render.draw_start)
		* data->wall_texture[data->render.wall_type].height
		/ (data->render.draw_end - data->render.draw_start);
	// Проверка выхода за границы текстуры
	if (data->render.tex_y >= 0 && data->render.tex_y
		< data->wall_texture[data->render.wall_type].height)
	{
		// Получение цвета из соответствующей текстуры
		data->render.color = ((int *)data->wall_texture[data
				->render.wall_type].data)[data->render.tex_y * (data
				->wall_texture[data->render.wall_type].size_line / 4)
			+ data->render.tex_x];
		// Рисование пикселя на экране
		((int *)data->data)[y * WIDTH + x] = data->render.color;
	}
}

/* 
The function  is responsible for rendering the 3D view of the game world 
	using raycasting.
Raycasting is a technique used to calculate the distance from the player 
to the walls in the game world and to determine what should be drawn on 
the screen. - roi 1030 
*/
void	ft_raycast(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	clear_screen(data);
	while (x < WIDTH)
	{
		raydir_calculation(data, x);
		step_determination(data);
		wallhit_detection(data);
		draw_calculation(data);
		texture_assign(data);
		y = data->render.draw_start;
		while (y <= data->render.draw_end)
		{
			draw_walls(data, x, y);
			y++;
		}
		x++;
	}
}
