/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:32:52 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/02 14:50:54 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libc/cub3d.h"

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

int	key_cross(t_game *data)
{
	int	i;

	i = 0;
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	while (i <= data->map_height)
		free(data->map2d[i++]);
	exit(0);
}

// int	main(int argc, char **argv)
// {
// 	t_game	game;

// 	if (argc < 1)
// 		printf("Error\nNot enough arguments\n");
// 	ft_memset(&game, 0, sizeof(t_game));
// 	game.ray = malloc(sizeof(t_ray));
// 	open_file(argv[1], &game);
// 	maps_checker(&game);
// 	player_position(&game);
// 	game.mlx = mlx_init();
// 	game.win = mlx_new_window(game.mlx, (game.map_width - 1) * 64, (game.map_height) * 64, "cub3d");
// 	mlx_loop_hook(game.mlx, raycasting, &game);
// 	image_in_map(&game);
// 	map_paint(&game);
// 	mlx_hook(game.win, 17, 0, key_cross, &game);
// 	mlx_loop(game.mlx);
// }

int main(int argc, char **argv)
{
    t_game game;

    if (argc < 2) {
        printf("Error\nNot enough arguments\n");
        return (1);
    }
    ft_memset(&game, 0, sizeof(t_game));
    game.ray = malloc(sizeof(t_ray));
    if (!game.ray) {
        printf("Error\nMemory allocation failed\n");
        return (1);
    }
    open_file(argv[1], &game);
    maps_checker(&game);
    player_position(&game);
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, 800, 600, "cub3D");
    image_in_map(&game);
    map_paint(&game);
    //mlx_loop_hook(game.mlx, raycasting, &game);
    mlx_hook(game.win, 17, 0, key_cross, &game);
    mlx_loop(game.mlx);

    // Cleanup
    free(game.ray);
    // Add any other cleanup necessary for your game (freeing textures, closing files, etc.)

    return (0);
}