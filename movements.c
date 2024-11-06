/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:14:08 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/06 15:14:35 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// void	move_with_slide(t_data *data, float move_x, float move_y)
// {
// 	if (data->map[(int)data->player_y][(int)(data->player_x + move_x)] != '1')
// 		data->player_x += move_x;
// 	if (data->map[(int)(data->player_y + move_y)][(int)data->player_x] != '1')
// 		data->player_y += move_y;
// }

int	move_a(t_data *data)
{
	float	move_y;
	float	move_x;

	move_x = cos((data->player_angle + 90) * M_PI / 180.0) * MOVE_SPEED;
	move_y = sin((data->player_angle + 90) * M_PI / 180.0) * MOVE_SPEED;
	if (data->map[(int)(data->player_y)][(int)(data->player_x - move_x)] != '1')
		data->player_x -= move_x;
	if (data->map[(int)(data->player_y - move_y)][(int)(data->player_x)] != '1')
		data->player_y -= move_y;
	ft_raycast(data);
	return (0);
}

int	move_d(t_data *data)
{
	float	move_y;
	float	move_x;

	move_x = cos((data->player_angle + 90) * M_PI / 180.0) * MOVE_SPEED;
	move_y = sin((data->player_angle + 90) * M_PI / 180.0) * MOVE_SPEED;
	if (data->map[(int)(data->player_y)][(int)(data->player_x + move_x)] != '1')
		data->player_x += move_x;
	if (data->map[(int)(data->player_y + move_y)][(int)(data->player_x)] != '1')
		data->player_y += move_y;
	ft_raycast(data);
	return (0);
}

int	move_w(t_data *data)
{
	float	move_x;
	float	move_y;

	move_x = cos(data->player_angle * M_PI / 180.0) * MOVE_SPEED;
	move_y = sin(data->player_angle * M_PI / 180.0) * MOVE_SPEED;
	if (data->map[(int)(data->player_y)][(int)(data->player_x + move_x)]
		!= '1' &&
		data->map[(int)(data->player_y + move_y)][(int)(data->player_x)] != '1')
	{
		data->player_x += move_x;
		data->player_y += move_y;
	}
	ft_raycast(data);
}

int	move_s(t_data *data)
{
	float	move_x;
	float	move_y;

	move_x = cos(data->player_angle * M_PI / 180.0) * MOVE_SPEED;
	move_y = sin(data->player_angle * M_PI / 180.0) * MOVE_SPEED;
	if (data->map[(int)(data->player_y)][(int)(data->player_x - move_x)]
		!= '1' &&
		data->map[(int)(data->player_y - move_y)][(int)(data->player_x)] != '1')
	{
		data->player_x -= move_x;
		data->player_y -= move_y;
	}
	ft_raycast(data);
}
