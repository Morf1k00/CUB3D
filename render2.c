/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:41:47 by oruban            #+#    #+#             */
/*   Updated: 2024/11/07 14:40:02 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ray_hits_x_axis(t_data *data)
{
	if (data->render.step_x > 0)
		data->render.wall_type = 0;
	else
		data->render.wall_type = 1;
}

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
