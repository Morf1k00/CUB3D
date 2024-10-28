/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:42:34 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/28 19:51:19 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

int	rotate_left(t_data *data)
{
	data->player_angle -= ROTATION_SPEED;
	if (data->player_angle < 0)
		data->player_angle += 360;
	ft_raycast(data);
}

int	rotate_right(t_data *data)
{
	data->player_angle += ROTATION_SPEED;
	if (data->player_angle >= 360)
		data->player_angle -= 360;
	ft_raycast(data);
}

/*  1028 
int can_move_to(t_data *data, double new_x, double new_y)
{
    int map_x = (int)new_x;
    int map_y = (int)new_y;

    // Check if the new position is within the bounds of the map
    if (map_x < 0 || map_x >= data->map_width || map_y < 0 || map_y >= data->map_height)
        return 0;

    // Check if the new position is a wall
    if (data->map[map_y][map_x] == '1')
        return 0;

    return 1;
}

void move_player(t_data *data, double move_x, double move_y)
{
    double new_x = data->player_x + move_x;
    double new_y = data->player_y + move_y;

    // Check if the player can move to the new position
    if (can_move_to(data, new_x, data->player_y))
        data->player_x = new_x;
    if (can_move_to(data, data->player_x, new_y))
        data->player_y = new_y;
}

void move_w(t_data *data)
{
    move_player(data, data->dir_x * MOVE_SPEED, data->dir_y * MOVE_SPEED);
    ft_raycast(data);
}

void move_s(t_data *data)
{
    move_player(data, -data->dir_x * MOVE_SPEED, -data->dir_y * MOVE_SPEED);
    ft_raycast(data);
}

void move_a(t_data *data)
{
    move_player(data, -data->plane_x * MOVE_SPEED, -data->plane_y * MOVE_SPEED);
    ft_raycast(data);
}

void move_d(t_data *data)
{
    move_player(data, data->plane_x * MOVE_SPEED, data->plane_y * MOVE_SPEED);
    ft_raycast(data);
}
 */

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	if (keycode == 65361)
		rotate_left(data);
	if (keycode == 65363)
		rotate_right(data);
	if (keycode == 119)
		move_w(data);
	else if (keycode == 115)
		move_s(data);
	else if (keycode == 97)
		move_a(data);
	else if (keycode == 100)
		move_d(data);
	else
		return (0);
}
