/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:42:34 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/08 15:53:02 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	printf("\n\t\033[0;31m\033[1m   GAME CLOSE\n\n");
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
	if (keycode == 97)
		move_a(data);
	if (keycode == 100)
		move_d(data);
	if (keycode == 115)
		move_s(data);
	else
		return (0);
}
