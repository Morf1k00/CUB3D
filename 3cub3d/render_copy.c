/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:14:09 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/08 16:57:31 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void ray_init(t_data *data)
{
    data->render.ray_angle = data->player_angle - (FOV / 2) + (data->render.x * (FOV / (float)WIDTH));
    data->render.ray_angle_rad = data->render.ray_angle * M_PI / 180.0;
    data->render.ray_dir_x = cos(data->render.ray_angle_rad);
    data->render.ray_dir_y = sin(data->render.ray_angle_rad);
    data->render.delta_dist_x = fabs(1 / data->render.ray_dir_x);
    data->render.delta_dist_y = fabs(1 / data->render.ray_dir_y);
    data->render.map_x = data->player_x;
    data->render.map_y = data->player_y;
    data->render.hit = 0;
}

void steps_rend(t_data *data)
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
        data->render.side_dist_y = (data->player_y -data->render. map_y) * data->render.delta_dist_y;
    } 
    else 
    {
        data->render.step_y = 1;
        data->render.side_dist_y = (data->render.map_y + 1.0 - data->player_y) * data->render.delta_dist_y;
    }
}

void dda_render(t_data *data)
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
        if (data->map[data->render.map_y][data->render.map_x] == 1)
            data->render.hit = 1; // Стена найдена
    }
}

void draw_wall(t_data *data)
{
    if (data->render.side == 0)
        data->render.perp_wall_dist = (data->render.map_x - data->player_x + (1 - data->render.step_x) / 2) / data->render.ray_dir_x;
    else
        data->render.perp_wall_dist = (data->render.map_y - data->player_y + (1 - data->render.step_y) / 2) / data->render.ray_dir_y;
    // Ограничить расстояние до MAX_DISTANCE
    if (data->render.perp_wall_dist > MAX_DISTANCE)
        data->render.perp_wall_dist = MAX_DISTANCE;
    // Рассчитать высоту стены на основе расстояния
    data->render.wall_height =(HEIGHT / data->render.perp_wall_dist);
    // Рассчитать, где начинать и заканчивать отрисовку стены
    data->render.draw_start = -(data->render.wall_height) / 2 + HEIGHT / 2;
    if (data->render.draw_start < 0)
        data->render.draw_start = 0;
    data->render.draw_end = data->render.wall_height / 2 + HEIGHT / 2;
    if (data->render.draw_end >= HEIGHT)
        data->render.draw_end = HEIGHT - 1;
}

void render(t_data *data)
{
    data->render.x = 0;
    clear_screen(data, FLOOR_COLOR); // Очистить экран (черный пол)
    while (data->render.x < WIDTH)
    {
        ray_init(data);
        // Рассчитать шаг и начальное side_dist
        steps_rend(data);
        // Выполнить DDA (Цифровой дифференциальный анализ) для определения стен
        dda_render(data);
        // Рассчитать расстояние до стены
        draw_wall(data);
        // Отрисовка текстуры на стене
        data->render.y = data->render.draw_start;
        while (data->render.y < data->render.draw_end)
        {
            data->render.tex_y = (data->render.y - data->render.draw_start) * data->wall_texture.height / (data->render.draw_end - data->render.draw_start);
            data->render.tex_x = (data->render.x * data->wall_texture.width) / WIDTH;
            // Получить цвет из текстуры
            data->render.color = ((int *)data->wall_texture.data)[data->render.tex_y * (data->wall_texture.size_line / 4) + data->render.tex_x];
            // Нарисовать пиксель
            ((int *)data->data)[data->render.y * WIDTH + data->render.x] = data->render.color;
            data->render.y++;  // Increment the y variable
        }
        data->render.x++;
    }
}