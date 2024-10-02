/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:57:50 by rkrechun          #+#    #+#             */
/*   Updated: 2024/09/11 14:21:03 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int handle_input(int keycode, t_game *game) 
{
    if (keycode == 65361 || keycode == 65363) {
        float angle_change = (keycode == 65361) ? -ROTATION_SPEED : ROTATION_SPEED;
        game->player->angle += angle_change;
        if (game->player->angle < 0) game->player->angle += 360;
        if (game->player->angle >= 360) game->player->angle -= 360;
    }

    if (keycode == 65362 || keycode == 65364) {
        float move_dir = (keycode == 65362) ? 1.0 : -1.0;
        float move_x = cos(game->player->angle * M_PI / 180.0) * MOVE_SPEED * move_dir;
        float move_y = sin(game->player->angle * M_PI / 180.0) * MOVE_SPEED * move_dir;

        if (game->map->map[(int)(game->player->y + move_y)][(int)(game->player->x + move_x)] == 0) {
            game->player->x += move_x;
            game->player->y += move_y;
        }
    }
}
