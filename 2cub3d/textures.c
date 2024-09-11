/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:56:06 by rkrechun          #+#    #+#             */
/*   Updated: 2024/09/11 15:00:07 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// Function to clear the screen with a specific color
void clear_screen(t_data *data, int color) {
    int x, y;
    y = 0;
    while (y < HEIGHT) {
        x = 0;
        while (x < WIDTH) {
            ((int *)data->data)[y * WIDTH + x] = color;
            x++;
        }
        y++;
    }
}

void load_texture(t_data *data, t_texture *texture, const char *file_path) {
    texture->img = mlx_xpm_file_to_image(data->mlx, (char *)file_path, &texture->width, &texture->height);
    if (!texture->img) {
        fprintf(stderr, "Failed to load texture: %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
    if (!texture->data) {
        fprintf(stderr, "Failed to get data address for texture: %s\n", file_path);
        exit(EXIT_FAILURE);
    }
}

void calculate_ray_direction(float ray_angle, float *ray_dir_x, float *ray_dir_y) {
    float ray_angle_rad = ray_angle * M_PI / 180.0;
    *ray_dir_x = cos(ray_angle_rad);
    *ray_dir_y = sin(ray_angle_rad);
}