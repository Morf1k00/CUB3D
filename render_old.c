/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:58:46 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/16 17:49:37 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ray_init(t_data *data)
{
	data->render.ray_angle = data->player_angle - (FOV / 2)
		+ (data->render.x * (FOV / (float)WIDTH));
	data->render.ray_angle_rad = data->render.ray_angle * M_PI / 180.0;
	data->render.ray_dir_x = cos(data->render.ray_angle_rad);
	data->render.ray_dir_y = sin(data->render.ray_angle_rad);
	data->render.delta_dist_x = fabs(1 / data->render.ray_dir_x);
	data->render.delta_dist_y = fabs(1 / data->render.ray_dir_y);
	data->render.map_x = data->player_x;
	data->render.map_y = data->player_y;
	data->render.hit = 0;
}

void	steps_rend(t_data *data)
{
	if (data->render.ray_dir_x < 0)
	{
		data->render.step_x = -1;
		data->render.side_dist_x = (data->player_x
				- data->render.map_x) * data->render.delta_dist_x;
	}
	else
	{
		data->render.step_x = 1;
		data->render.side_dist_x = (data->render.map_x
				+ 1.0 - data->player_x) * data->render.delta_dist_x;
	}
	if (data->render.ray_dir_y < 0)
	{
		data->render.step_y = -1;
		data->render.side_dist_y = (data->player_y
				- data->render. map_y) * data->render.delta_dist_y;
	}
	else
	{
		data->render.step_y = 1;
		data->render.side_dist_y = (data->render.map_y + 1.0
				- data->player_y) * data->render.delta_dist_y;
	}
}

// void	dda_render(t_data *data)
// {
// 	while (!data->render.hit)
// 	{
// 		if (data->render.side_dist_x < data->render.side_dist_y)
// 		{
// 			data->render.side_dist_x += data->render.delta_dist_x;
// 			data->render.map_x += data->render.step_x;
// 			data->render.side = 0;
// 		}
// 		else
// 		{
// 			data->render.side_dist_y += data->render.delta_dist_y;
// 			data->render.map_y += data->render.step_y;
// 			data->render.side = 1;
// 		}
// 		if (data->map[data->render.map_y][data->render.map_x] == 1)
// 			data->render.hit = 1;
// 	}
// }

void	dda_render(t_data *data)
{
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
		{
			data->render.hit = 1;
			break ;
		}
		if (data->map[data->render.map_y][data->render.map_x] == '1')
			data->render.hit = 1;
	}
}

void	draw_wall(t_data *data)
{
	if (data->render.side == 0)
		data->render.perp_wall_dist = (data->render.map_x - data->player_x
				+ (1 - data->render.step_x) / 2) / data->render.ray_dir_x;
	else
		data->render.perp_wall_dist = (data->render.map_y - data->player_y
				+ (1 - data->render.step_y) / 2) / data->render.ray_dir_y;
	if (data->render.perp_wall_dist > MAX_DISTANCE)
		data->render.perp_wall_dist = MAX_DISTANCE;
	data->render.wall_height = (HEIGHT / data->render.perp_wall_dist);
	data->render.draw_start = -(data->render.wall_height) / 2 + HEIGHT / 2;
	if (data->render.draw_start < 0)
		data->render.draw_start = 0;
	data->render.draw_end = data->render.wall_height / 2 + HEIGHT / 2;
	if (data->render.draw_end >= HEIGHT)
		data->render.draw_end = HEIGHT - 1;
}

void	render(t_data *data)
{
	data->render.x = 0;
	clear_screen(data);
	while (data->render.x < WIDTH)
	{
		ray_init(data);
		steps_rend(data);
		dda_render(data);
		draw_wall(data);
		data->render.y = data->render.draw_start;
		while (data->render.y < data->render.draw_end)
		{
			data->render.tex_y = (data->render.y - data->render.draw_start)
				* data->wall_texture.height / (data->render.draw_end
					- data->render.draw_start);
			data->render.tex_x = (data->render.x * data->wall_texture.width)
				/ WIDTH;
			data->render.color = ((int *)data->wall_texture.data)
			[data->render.tex_y * (data->wall_texture.size_line / 4)
				+ data->render.tex_x];
			((int *)data->data)[data->render.y * WIDTH + data->render.x]
				= data->render.color;
			data->render.y++;
		}
		data->render.x++;
	}
}
