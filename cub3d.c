/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:27:46 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/04 18:20:02 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	load_textures(t_data *data)
{
	int	width;
	int	height;
	int	i;

	i = 0;
	while (i < 4)
	{
		data->wall_texture[i].img = mlx_xpm_file_to_image(data->mlx,
				data->wall_texture[i].path, &width, &height);
		if (!data->wall_texture[i].img)
		{
			printf("Error loading texture file: %s\n",
				data->wall_texture[i].path);
			exit(EXIT_FAILURE);
		}
		data->wall_texture[i].width = width;
		data->wall_texture[i].height = height;
		data->wall_texture[i].data = mlx_get_data_addr(
				data->wall_texture[i].img, &data->wall_texture[i].bpp,
				&data->wall_texture[i].size_line,
				&data->wall_texture[i].endian);
		i++;
	}
}

/* 
	 Clears the screen by filling it with the ceiling and floor colors.-1030 roi
 */
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
	int		i;

	i = -1;
	init_data(&data);
	open_file(arv[1], &data);
	printf("%i\n", data.map_width);
	map_rewrite(&data);
	while (++i < data.map_height)
		printf("%s", data.map[i]);
	finder_coordinate(&data, arv[1]);
	player_position(&data);
	check_walls(&data);
	load_textures(&data);
	printf("Player x: %i\n", (int)data.player_x);
	printf("Player y: %f\n", data.player_y);
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