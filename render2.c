/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:41:47 by oruban            #+#    #+#             */
/*   Updated: 2024/10/30 16:45:56 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/* 
	refactoring of render.c - 1030 roi
 */

/* 
	function is the result of refactoring 2 shorten texture_assign till 25 lines
	1030 - roi

		if (data->render.step_x > 0)
			data->render.wall_type = 0; // East wall
		else
			data->render.wall_type = 1; // West wall
 */
void	ray_hits_x_axis(t_data *data)
{
	if (data->render.step_x > 0)
		data->render.wall_type = 0;
	else
		data->render.wall_type = 1;
}

/* 	
	Determines which texture to use for the wall and calculates the texture 
	coordinates. - roi 1030 
		wall_hit - the variable specifically represents th fractional part of th
		intersection point along the wall.  2 determine
		th texture coordinate. This value is used 2 map th correct part of th
		texture onto th wall slice being drawn.
		
		// th ray hs hit a vertical wall (along the x-axis)
		if (data->render.side == 0) 
		{
			ray_hits_x_axis(data);
			wall_hit = data->player_y + data->render.perp_wall_dist
				* data->render.ray_dir_y;
		}
		else // th ray hs hit a vertical wall (along the y-axis)
		{
			if (data->render.step_y > 0)
				data->render.wall_type = 2; // North wall
			else
				data->render.wall_type = 3; // South wall
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
*/
void	texture_assign(t_data *data)
{
	double	wall_hit;

	if (data->render.side == 0)
	{
		ray_hits_x_axis(data);
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
 The function is drawing a vertical slice of a wall on the screen.
 This function uses texture mapping to apply the correct texture to the wall 
 slice based on the calculated texture coordinates. - roi 1030

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
 */
void	draw_walls(t_data *data, int x, int y)
{
	data->render.tex_y = (y - data->render.draw_start)
		* data->wall_texture[data->render.wall_type].height
		/ (data->render.draw_end - data->render.draw_start);
	if (data->render.tex_y >= 0 && data->render.tex_y
		< data->wall_texture[data->render.wall_type].height)
	{
		data->render.color = ((int *)data->wall_texture[data
				->render.wall_type].data)[data->render.tex_y * (data
				->wall_texture[data->render.wall_type].size_line / 4)
			+ data->render.tex_x];
		((int *)data->data)[y * WIDTH + x] = data->render.color;
	}
}
