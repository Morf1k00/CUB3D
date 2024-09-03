/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:48:27 by rkrechun          #+#    #+#             */
/*   Updated: 2024/09/02 15:29:36 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libc/cub3d.h"

void image_in_map(t_game *game)
{
	int i;
	int j;

	game->img = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", &i, &j);
}

void map_paint(t_game *dat)
{
	int h;
	int w;

	h = 0;
	while(h <= dat->map_height)
	{
		w = 0;
		while (dat->map2d[h][w])
		{
			if (dat->map2d[h][w] == '1' || dat->map2d[h][w] == '0')
				mlx_put_image_to_window(dat->mlx, dat->win, dat->img, w * 64, h * 64);
			w++;
		}
		h++;
	}
}

