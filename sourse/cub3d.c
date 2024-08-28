/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:32:52 by rkrechun          #+#    #+#             */
/*   Updated: 2024/08/28 13:46:50 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libc/cub3d.h"

void start_game_loop(t_data *dat)
{
	t_mlx *mlx_t;

	mlx_t->dat = dat;
	mlx_t->mlx = mlx_init();
	mlx_t->win = mlx_new_window(mlx_t->mlx, 800, 600, "Hello world!");
	mlx_loop(mlx_t->mlx);
}

int main(int argc, char **argv)
{
	t_data *dat;

	if (argc < 3)
		printf("Error\nNot enough arguments\n");
	dat = calloc(1, sizeof(t_data));
	open_file(argv[1], dat);
	parse_map(dat);
	parse_wigth(dat);
	player_position(dat);
	start_game_loop(dat);
}