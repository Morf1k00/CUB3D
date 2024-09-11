/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:52:17 by rkrechun          #+#    #+#             */
/*   Updated: 2024/09/04 15:43:52 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int raycasting(void *param)
// {
//     t_game *game = (t_game *)param;
//     int x = 0;
//     while (x < game->map_width)
//     {
//         double camera_x = 2 * x / (double)(game->map_width) - 1;
//         game->ray->ray_dir_x = game->ray->dir_x + game->ray->plane_x * camera_x;
//         game->ray->ray_dir_y = game->ray->dir_y + game->ray->plane_y * camera_x;
//         game->ray->map_x = (int)(game->ray->player_x);
//         game->ray->map_y = (int)(game->ray->player_y);
//         game->ray->delta_dist_x = fabs(1 / game->ray->ray_dir_x);
//         game->ray->delta_dist_y = fabs(1 / game->ray->ray_dir_y);
//         if (game->ray->ray_dir_x < 0)
//         {
//             game->ray->step_x = -1;
//             game->ray->side_dist_x = (game->ray->player_x - game->ray->map_x) * game->ray->delta_dist_x;
//         }
//         else
//         {
//             game->ray->step_x = 1;
//             game->ray->side_dist_x = (game->ray->map_x + 1.0 - game->ray->player_x) * game->ray->delta_dist_x;
//         }
//         if (game->ray->ray_dir_y < 0)
//         {
//             game->ray->step_y = -1;
//             game->ray->side_dist_y = (game->ray->player_y - game->ray->map_y) * game->ray->delta_dist_y;
//         }
//         else
//         {
//             game->ray->step_y = 1;
//             game->ray->side_dist_y = (game->ray->map_y + 1.0 - game->ray->player_y) * game->ray->delta_dist_y;
//         }
//         while (1)
//         {
//             if (game->ray->side_dist_x < game->ray->side_dist_y)
//             {
//                 game->ray->side_dist_x += game->ray->delta_dist_x;
//                 game->ray->map_x += game->ray->step_x;
//                 game->ray->side = 0;
//             }
//             else
//             {
//                 game->ray->side_dist_y += game->ray->delta_dist_y;
//                 game->ray->map_y += game->ray->step_y;
//                 game->ray->side = 1;
//             }
//             if (game->map2d[game->ray->map_y][game->ray->map_x] == '1')
//                 break;
//         }
//         if (game->ray->side == 0)
//             game->ray->perp_wall_dist = (game->ray->map_x - game->ray->player_x + (1 - game->ray->step_x) / 2) / game->ray->ray_dir_x;
//         else
//             game->ray->perp_wall_dist = (game->ray->map_y - game->ray->player_y + (1 - game->ray->step_y) / 2) / game->ray->ray_dir_y;
//         int line_height = (int)(game->map_height / game->ray->perp_wall_dist);
//         int draw_start = -line_height / 2 + game->map_height / 2;
//         if (draw_start < 0)
//             draw_start = 0;
//         int draw_end = line_height / 2 + game->map_height / 2;
//         if (draw_end >= game->map_height)
//             draw_end = game->map_height - 1;
//         int color = 0x00FF00;
//         if (game->ray->side == 1)
//             color = color / 2;
//         int y = draw_start;
//         while (y < draw_end)
//         {
//             mlx_pixel_put(game->mlx, game->win, x, y, color);
//             y++;
//         }
//         x++;
//     }
//     return (0);
// }

// int raycasting(void *param)
// {
//     t_game *game = (t_game *)param;
//     int x = 0;
//     while (x < game->map_width)
//     {
//         double camera_x = 2 * x / (double)(game->map_width) - 1;
//         game->ray->ray_dir_x = game->ray->dir_x + game->ray->plane_x * camera_x;
//         game->ray->ray_dir_y = game->ray->dir_y + game->ray->plane_y * camera_x;
//         game->ray->map_x = (int)(game->ray->player_x);
//         game->ray->map_y = (int)(game->ray->player_y);
//         game->ray->delta_dist_x = fabs(1 / game->ray->ray_dir_x);
//         game->ray->delta_dist_y = fabs(1 / game->ray->ray_dir_y);
//         if (game->ray->ray_dir_x < 0)
//         {
//             game->ray->step_x = -1;
//             game->ray->side_dist_x = (game->ray->player_x - game->ray->map_x) * game->ray->delta_dist_x;
//         }
//         else
//         {
//             game->ray->step_x = 1;
//             game->ray->side_dist_x = (game->ray->map_x + 1.0 - game->ray->player_x) * game->ray->delta_dist_x;
//         }
//         if (game->ray->ray_dir_y < 0)
//         {
//             game->ray->step_y = -1;
//             game->ray->side_dist_y = (game->ray->player_y - game->ray->map_y) * game->ray->delta_dist_y;
//         }
//         else
//         {
//             game->ray->step_y = 1;
//             game->ray->side_dist_y = (game->ray->map_y + 1.0 - game->ray->player_y) * game->ray->delta_dist_y;
//         }
//         while (1)
//         {
//             if (game->ray->side_dist_x < game->ray->side_dist_y)
//             {
//                 game->ray->side_dist_x += game->ray->delta_dist_x;
//                 game->ray->map_x += game->ray->step_x;
//                 game->ray->side = 0;
//             }
//             else
//             {
//                 game->ray->side_dist_y += game->ray->delta_dist_y;
//                 game->ray->map_y += game->ray->step_y;
//                 game->ray->side = 1;
//             }
//             if (game->map2d[game->ray->map_y][game->ray->map_x] == '1')
//                 break;
//         }
//         if (game->ray->side == 0)
//             game->ray->perp_wall_dist = (game->ray->map_x - game->ray->player_x + (1 - game->ray->step_x) / 2) / game->ray->ray_dir_x;
//         else
//             game->ray->perp_wall_dist = (game->ray->map_y - game->ray->player_y + (1 - game->ray->step_y) / 2) / game->ray->ray_dir_y;
//         int line_height = (int)(game->map_height / game->ray->perp_wall_dist);
//         int draw_start = -line_height / 2 + game->map_height / 2;
//         if (draw_start < 0)
//             draw_start = 0;
//         int draw_end = line_height / 2 + game->map_height / 2;
//         if (draw_end >= game->map_height)
//             draw_end = game->map_height - 1;
//         int color = 0x00FF00;
//         if (game->ray->side == 1)
//             color = color / 2;
//         // Clear previous frame data here
//         int y = draw_start;
//         while (y < draw_end)
//         {
//             mlx_pixel_put(game->mlx, game->win, x, y, color);
//             y++;
//         }
//         x++;
//     }
//     return (0);
// }

int raycasting(void *param)
{
    t_game *game = (t_game *)param;
    int x = 0;

    while (x < game->map_width)
    {
        double camera_x = 2 * x / (double)(game->map_width) - 1;
        double ray_dir_x = game->ray->dir_x + game->ray->plane_x * camera_x;
        double ray_dir_y = game->ray->dir_y + game->ray->plane_y * camera_x;
        int map_x = (int)game->ray->player_x;
        int map_y = (int)game->ray->player_y;
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        int step_x, step_y;
        double side_dist_x, side_dist_y;
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (game->ray->player_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->ray->player_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (game->ray->player_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->ray->player_y) * delta_dist_y;
        }
        int hit = 0;
        int side;
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (game->map2d[map_y][map_x] == '1') hit = 1;
        }
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (map_x - game->ray->player_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - game->ray->player_y + (1 - step_y) / 2) / ray_dir_y;
        int line_height = (int)(game->map_height / perp_wall_dist);
        int draw_start = -line_height / 2 + game->map_height / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + game->map_height / 2;
        if (draw_end >= game->map_height)
            draw_end = game->map_height - 1;
        int color = 0x00FF00;
        if (side == 1) color = color / 2;

        for (int y = draw_start; y < draw_end; y++)
        {
            mlx_pixel_put(game->mlx, game->win, x, y, color);
        }

        x++;
    }
    return (0);
}