/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:57:11 by rkrechun          #+#    #+#             */
/*   Updated: 2024/09/11 14:14:17 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int game_loop(t_game *game) {
    render(game);
    mlx_put_image_to_window(game->mlx_data->mlx, game->mlx_data->win, game->mlx_data->img, 0, 0);
    return 0;
}

int main() {
    t_data mlx_data;
    t_texture wall_texture;
    t_player player = { 2.5, 1.5, 90 };
    t_map map = { MAP_WIDTH, MAP_HEIGHT, {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1}
    }};
    
    t_game game = { &mlx_data, &wall_texture, &player, &map };

    // Initialize MLX
    mlx_data.mlx = mlx_init();
    mlx_data.win = mlx_new_window(mlx_data.mlx, WIDTH, HEIGHT, "Cub3D");
    mlx_data.img = mlx_new_image(mlx_data.mlx, WIDTH, HEIGHT);
    mlx_data.data = mlx_get_data_addr(mlx_data.img, &mlx_data.bpp, &mlx_data.size_line, &mlx_data.endian);

    // Load textures
    load_texture(&mlx_data, &wall_texture, "wall.xpm");

    // Set hooks
    mlx_hook(mlx_data.win, 2, 1L << 0, handle_input, &game);
    mlx_loop_hook(mlx_data.mlx, game_loop, &game);

    // Start the game loop
    mlx_loop(mlx_data.mlx);

    // Clean up
    mlx_destroy_image(mlx_data.mlx, mlx_data.img);
    mlx_destroy_window(mlx_data.mlx, mlx_data.win);
    mlx_destroy_display(mlx_data.mlx);
    free(mlx_data.mlx);
    return 0;
}
