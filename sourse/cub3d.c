/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:32:52 by rkrechun          #+#    #+#             */
/*   Updated: 2024/09/02 16:02:44 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libc/cub3d.h"

void start_game_loop(t_game *dat)
{
	dat->mlx = mlx_init();
	dat->win = mlx_new_window(dat->mlx, (dat->map_height + 1) * 64, (dat->map_width + 1) * 64, "cub3d");
	mlx_loop(dat->mlx);
	if (dat->map2d)
		free(dat->map2d);
}

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}


int	main(int argc, char **argv)
{
	t_game	game;

	if (argc < 1)
		printf("Error\nNot enough arguments\n");
	ft_memset(&game, 0, sizeof(t_game));
	// game = calloc(1, sizeof(t_game));
	open_file(argv[1], &game);
	maps_checker(&game);
	// image_in_map(&game);
	player_position(&game);
	// start_game_loop(&game);
}
