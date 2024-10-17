/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:27:46 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/17 14:24:57 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	load_textures(t_data *data)
{
	int	width;
	int	height;

	data->wall_texture.img = mlx_xpm_file_to_image(data->mlx,
			"walls1.xpm", &width, &height);
	if (!data->wall_texture.img)
	{
		printf("Error loading texture file.\n");
		exit(EXIT_FAILURE);
	}
	data->wall_texture.width = width;
	data->wall_texture.height = height;
	data->wall_texture.data = mlx_get_data_addr(data->wall_texture.img,
			&data->wall_texture.bpp, &data->wall_texture.size_line,
			&data->wall_texture.endian);
}

void	clear_screen(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT / 2)
	{
		while (x < WIDTH)
		{
			((int *)data->data)[y * WIDTH + x] = data->color_c;
			x++;
		}
		x = 0;
		y++;
	}
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			((int *)data->data)[y * WIDTH + x] = data->color_f;
			x++;
		}
		x = 0;
		y++;
	}
}

int	game_loop(t_data *data)
{
	// render(data);
	ft_raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		fprintf(stderr, "Failed to initialize MLX\n");
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		fprintf(stderr, "Failed to create window\n");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		fprintf(stderr, "Failed to create image\n");
	data->data = mlx_get_data_addr(data->img, &data->bpp,
			&data->size_line, &data->endian);
	if (!data->data)
		fprintf(stderr, "Failed to get image data address\n");
}

int	main(int arc, char **arv)
{
	t_data	data;

	init_data(&data);
	finder_coordinate(&data, arv[1]);
	open_file(arv[1], &data);
	player_position(&data);
	load_textures(&data);
	mlx_hook(data.win, 2, 1L << 0, handle_key_press, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, data.img);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
// maps_checker(&data);