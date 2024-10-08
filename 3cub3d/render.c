/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:14:09 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/08 14:26:24 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void render(t_data *data)
{
    clear_screen(data, FLOOR_COLOR); // Очистить экран (черный пол)

    int x = 0;
    while (x < WIDTH)
    {
        // Рассчитать угол луча относительно игрока
        float ray_angle = data->player_angle - (FOV / 2) + (x * (FOV / (float)WIDTH));
        // Преобразовать ray_angle из градусов в радианы
        float ray_angle_rad = ray_angle * M_PI / 180.0;
        // Направление луча
        float ray_dir_x = cos(ray_angle_rad);
        float ray_dir_y = sin(ray_angle_rad);
        // Переменные для шага и расчета расстояний
        float delta_dist_x = fabs(1 / ray_dir_x);
        float delta_dist_y = fabs(1 / ray_dir_y);
        int map_x = data->player_x;
        int map_y = data->player_y;
        float side_dist_x;
        float side_dist_y;
        int step_x;
        int step_y;
        int hit = 0;
        int side; // 0 для вертикальной стены, 1 для горизонтальной стены
        // Рассчитать шаг и начальное side_dist
        if (ray_dir_x < 0) 
        {
            step_x = -1;
            side_dist_x = (data->player_x - map_x) * delta_dist_x;
        }
        else 
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - data->player_x) * delta_dist_x;
        }
        if (ray_dir_y < 0) 
        {
            step_y = -1;
            side_dist_y = (data->player_y - map_y) * delta_dist_y;
        } 
        else 
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - data->player_y) * delta_dist_y;
        }
        // Выполнить DDA (Цифровой дифференциальный анализ) для определения стен
        while (!hit)
        {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (data->map[map_y][map_x] == 1)
                hit = 1; // Стена найдена
        }
        // Рассчитать расстояние до стены
        float perp_wall_dist;
        if (side == 0) perp_wall_dist = (map_x - data->player_x + (1 - step_x) / 2) / ray_dir_x;
        else perp_wall_dist = (map_y - data->player_y + (1 - step_y) / 2) / ray_dir_y;
        // Ограничить расстояние до MAX_DISTANCE
        if (perp_wall_dist > MAX_DISTANCE) perp_wall_dist = MAX_DISTANCE;
        // Рассчитать высоту стены на основе расстояния
        int wall_height =(HEIGHT / perp_wall_dist);
        // Рассчитать, где начинать и заканчивать отрисовку стены
        int draw_start = -wall_height / 2 + HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = wall_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;
        // Отрисовка текстуры на стене
        for (int y = draw_start; y < draw_end; y++) {
            int tex_y = (y - draw_start) * data->wall_texture.height / (draw_end - draw_start);
            int tex_x = (x * data->wall_texture.width) / WIDTH;
            // Получить цвет из текстуры
            int color = ((int *)data->wall_texture.data)[tex_y * (data->wall_texture.size_line / 4) + tex_x];
            // Нарисовать пиксель
            ((int *)data->data)[y * WIDTH + x] = color;
        }
        x++;
    }
}