/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:14:08 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/06 13:13:39 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "game.h"

int	move_a(t_data *data)
{
	float	move_y;
	float	move_x;

	move_x = cos((data->player_angle + 90) * M_PI / 180.0) * MOVE_SPEED;
	move_y = sin((data->player_angle + 90) * M_PI / 180.0) * MOVE_SPEED;
	if (data->map[(int)(data->player_y + move_y)]
		[(int)(data->player_x + move_x)] == 48)
	{
		data->player_x -= move_x;
		data->player_y -= move_y;
	}
	ft_raycast(data);
}

int	move_d(t_data *data)
{
	float	move_y;
	float	move_x;

	move_x = cos((data->player_angle + 90) * M_PI / 180.0) * MOVE_SPEED;
	move_y = sin((data->player_angle + 90) * M_PI / 180.0) * MOVE_SPEED;
	if (data->map[(int)(data->player_y + move_y)]
		[(int)(data->player_x + move_x)] == 48)
	{
		data->player_x += move_x;
		data->player_y += move_y;
	}
	ft_raycast(data);
}

int	move_w(t_data *data)
{
	float	move_x;
	float	move_y;

	move_x = cos(data->player_angle * M_PI / 180.0) * MOVE_SPEED;
	move_y = sin(data->player_angle * M_PI / 180.0) * MOVE_SPEED;
	if (data->map[(int)(data->player_y + move_y)]
		[(int)(data->player_x + move_x)] == 48)
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
	if (data->map[(int)(data->player_y - move_y)]
		[(int)(data->player_x - move_x)] == 48)
	{
		data->player_x -= move_x;
		data->player_y -= move_y;
	}
	ft_raycast(data);
} */



#include "game.h"

int move_a(t_data *data)
{
    float move_x = data->plane_x * MOVE_SPEED;
    float move_y = data->plane_y * MOVE_SPEED;

    if (data->map[(int)(data->player_y - move_y)][(int)(data->player_x - move_x)] == '0')
    {
        data->player_x -= move_x;
        data->player_y -= move_y;
    }
    ft_raycast(data);
    return (0);
}

int move_d(t_data *data)
{
    float move_x = data->plane_x * MOVE_SPEED;
    float move_y = data->plane_y * MOVE_SPEED;

    if (data->map[(int)(data->player_y + move_y)][(int)(data->player_x + move_x)] == '0')
    {
        data->player_x += move_x;
        data->player_y += move_y;
    }
    ft_raycast(data);
    return (0);
}

int move_w(t_data *data)
{
    float move_x = data->render.ray_dir_x * MOVE_SPEED;
    float move_y = data->render.ray_dir_y * MOVE_SPEED;

    if (data->map[(int)(data->player_y + move_y)][(int)(data->player_x + move_x)] == '0')
    {
        data->player_x += move_x;
        data->player_y += move_y;
    }
    ft_raycast(data);
    return (0);
}

int move_s(t_data *data)
{
    float move_x = data->render.ray_dir_x * MOVE_SPEED;
    float move_y = data->render.ray_dir_y * MOVE_SPEED;

    if (data->map[(int)(data->player_y - move_y)][(int)(data->player_x - move_x)] == '0')
    {
        data->player_x -= move_x;
        data->player_y -= move_y;
    }
    ft_raycast(data);
    return (0);
}