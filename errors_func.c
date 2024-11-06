/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:36:55 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/06 16:05:40 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void 	clean_memory(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (i < data->map_height)
			free(data->map[i++]);
		free(data->map);
	}
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	// free(data->render);
	
	i = 0;
	while (i < 4)
	{
		free(data->wall_texture[i].data);
		free(data->wall_texture[i].img);
		i++;
	}
	free(data->mlx);
	free(data->win);
	free(data->data);
	free(data);
}

void 	prog_exit(char *message, t_data *data, int error_code)
{
	if (error_code == 1)
		fprintf(stderr, "%s\n", message);

	clean_memory(data);
	exit(error_code);
}