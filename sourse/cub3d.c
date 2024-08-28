/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:32:52 by rkrechun          #+#    #+#             */
/*   Updated: 2024/08/28 17:14:03 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libc/cub3d.h"

// void start_game_loop(t_data *dat)
// {
// 	t_mlx *mlx;

// 	// mlx_t->dat = dat;
// 	mlx->mlx = mlx_init();
// 	mlx->win = mlx_new_window(mlx->mlx, 800, 600, "Hello world!");
// 	mlx_loop(mlx->mlx);
// 	if (mlx->dat->map2d)
// 		free(dat->map2d);
	
// }

int main(int argc, char **argv)
{
	t_data *dat;

	if (argc < 1)
		printf("Error\nNot enough arguments\n");
	dat = calloc(1, sizeof(t_data));
	open_file(argv[1], dat);
	// int i = 0;
	// while (dat->map2d[i])
	// {
	// 	printf("%s", dat->map2d[i]);
	// 	i++;
	// }
	// parse_map(dat);
	// parse_wigth(dat);
	maps_checker(dat);
	player_position(dat);
	// start_game_loop(dat);
}