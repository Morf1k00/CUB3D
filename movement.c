/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:42:34 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/06 15:51:56 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

 
// created to avoid diagonal movement by W and S keys - update_direction_vectors(data);
 
void update_direction_vectors(t_data *data)
{
    // Update the direction vector
    data->render.ray_dir_x = cos(data->player_angle * M_PI / 180.0);
    data->render.ray_dir_y = sin(data->player_angle * M_PI / 180.0);

    // Update the camera plane (perpendicular to the direction vector)
    data->plane_x = -data->render.ray_dir_y * tan(FOV / 2.0 * M_PI / 180.0);
    data->plane_y = data->render.ray_dir_x * tan(FOV / 2.0 * M_PI / 180.0);
	// Debugging information
    printf("update_direction_vectors: ray_dir_x = %f, ray_dir_y = %f\n", data->render.ray_dir_x, data->render.ray_dir_y);
    printf("update_direction_vectors: plane_x = %f, plane_y = %f\n", data->plane_x, data->plane_y);
}

int	rotate_left(t_data *data)
{
	data->player_angle -= ROTATION_SPEED;
	if (data->player_angle < 0)
		data->player_angle += 360;
	update_direction_vectors(data); // update_direction_vectors(data);
	ft_raycast(data);
}

int	rotate_right(t_data *data)
{
	data->player_angle += ROTATION_SPEED;
	if (data->player_angle >= 360)
		data->player_angle -= 360;
	update_direction_vectors(data); // update_direction_vectors(data);
	ft_raycast(data);
}

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
