/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:10:39 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/17 14:27:02 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	walltype_detection(t_data *data)
{
	if (data->render.side == 0)
	{
		if (data->render.ray_dir_x <= 0)
			data->render.tex_x = 1;  // Западная стена
		else
			data->render.tex_x = 0;  // Восточная стена
	}
	else
	{
		if (data->render.ray_dir_y >= 0)
			data->render.tex_x = 3;  // Северная стена
		else
			data->render.tex_x = 2;  // Южная стена
	}
}

void	step_determination(t_data *data)
{
	if (data->render.ray_dir_x < 0)
	{
		data->render.step_x = -1;
		data->render.side_dist_x = (data->player_x - data->render.map_x) * data->render.delta_dist_x;
	}
	else
	{
		data->render.step_x = 1;
		data->render.side_dist_x = (data->render.map_x + 1.0 - data->player_x) * data->render.delta_dist_x;
	}
	if (data->render.ray_dir_y < 0)
	{
		data->render.step_y = -1;
		data->render.side_dist_y = (data->player_y - data->render.map_y) * data->render.delta_dist_y;
	}
	else
	{
		data->render.step_y = 1;
		data->render.side_dist_y = (data->render.map_y + 1.0 - data->player_y) * data->render.delta_dist_y;
	}
}

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
		// Проверка выхода за пределы карты
		if (data->render.map_x < 0 || data->render.map_x >= data->map_width
			|| data->render.map_y < 0 || data->render.map_y >= data->map_height)
			break;
		// Проверка на столкновение со стеной
		if (data->map[data->render.map_y][data->render.map_x] == '1')
			data->render.hit = 1;
	}
}

void	raydir_calculation(t_data *data, int x)
{
	// Рассчет угла луча
	data->render.ray_angle = data->player_angle - (FOV / 2.0) + (x * (FOV / (float)WIDTH));
	data->render.ray_angle_rad = data->render.ray_angle * M_PI / 180.0;
	data->render.ray_dir_x = cos(data->render.ray_angle_rad);
	data->render.ray_dir_y = sin(data->render.ray_angle_rad);
	data->render.delta_dist_x = fabs(1 / data->render.ray_dir_x);
	data->render.delta_dist_y = fabs(1 / data->render.ray_dir_y);
	data->render.map_x = (int)data->player_x;
	data->render.map_y = (int)data->player_y;
	data->render.hit = 0;
}

void	draw_calculation(t_data *data)
{
	if (data->render.side == 0)
		data->render.perp_wall_dist = (data->render.map_x - data->player_x + (1 - data->render.step_x) / 2) / data->render.ray_dir_x;
	else
		data->render.perp_wall_dist = (data->render.map_y - data->player_y + (1 - data->render.step_y) / 2) / data->render.ray_dir_y;

	// Ограничение максимального расстояния
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

void	texture_assign(t_data *data)
{
	double	wall_hit;

	if (data->render.side == 0)
		wall_hit = data->player_y + data->render.perp_wall_dist * data->render.ray_dir_y;
	else
		wall_hit = data->player_x + data->render.perp_wall_dist * data->render.ray_dir_x;

	wall_hit -= floor(wall_hit);
	data->render.tex_x = (int)(wall_hit * (double)data->wall_texture.width);
}

void	draw_walls(t_data *data, int x, int y)
{
	data->render.tex_y = (y - data->render.draw_start) * data->wall_texture.height / (data->render.draw_end - data->render.draw_start);
	data->render.color = ((int *)data->wall_texture.data)[data->render.tex_y * (data->wall_texture.size_line / 4) + data->render.tex_x];
	((int *)data->data)[y * WIDTH + x] = data->render.color;
}

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
		walltype_detection(data);
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
