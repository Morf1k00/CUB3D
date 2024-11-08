/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:36:55 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/08 15:52:47 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	clean_memory(t_data *data)
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
	i = 0;
	while (i < 4)
	{
		if (data->wall_texture[i].img)
			free(data->wall_texture[i].img);
		i++;
	}
}

void	prog_exit(char *message, t_data *data, int error_code)
{
	if (error_code == 1)
		fprintf(stderr, "\n\n\t\t\033[31m%s\033[0m\n", message);
	clean_memory(data);
	exit(error_code);
}

void	simple_exit(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
