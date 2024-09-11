/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:56:33 by rkrechun          #+#    #+#             */
/*   Updated: 2024/09/11 16:10:06 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void raydir_x(float ray_dir_x, int *step_x, float *side_dist_x, int *map_x, t_game *game)
{
	float delta_dist_x;
	
	
    delta_dist_x = fabs(1 / ray_dir_x);
	if (ray_dir_x < 0) 
	{
		*step_x = -1;
		*side_dist_x = (game->player->x - *map_x) * delta_dist_x;
	}
	else
	{
		*step_x = 1;
		*side_dist_x = (*map_x + 1.0 - game->player->x) * delta_dist_x;
	}
}

void raydir_y(float ray_dir_y, int *step_y, float *side_dist_y, int *map_y, t_game *game)
{
	float delta_dist_y;
	
	delta_dist_y = fabs(1 / ray_dir_y);
	if (ray_dir_y < 0) 
	{
		*step_y = -1;
		*side_dist_y = (game->player->y - *map_y) * delta_dist_y;
	}
	else
	{
		*step_y = 1;
		*side_dist_y = (*map_y + 1.0 - game->player->y) * delta_dist_y;
	}
}

void if_side_x(float *side_dist_x, float *delta_dist_x, int *map_x, int *step_x, int *side)
{
	*side_dist_x += *delta_dist_x;
	*map_x += *step_x;
	*side = 0;
}

void if_side_y(float *side_dist_y, float *delta_dist_y, int *map_y, int *step_y, int *side)
{
	*side_dist_y += *delta_dist_y;
	*map_y += *step_y;
	*side = 1;
}

float	perform_dda(float ray_dir_x, float ray_dir_y, t_game *game, int *side) 
{
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;

	map_x = (int)game->player->x;
	map_y = (int)game->player->y;
	hit = 0;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	raydir_x(ray_dir_x, &step_x, &side_dist_x, &map_x, game);
	raydir_y(ray_dir_y, &step_y, &side_dist_y, &map_y, game);
	while (!hit)
	{
		if (side_dist_x < side_dist_y) 
			if_side_x(&side_dist_x, &delta_dist_x, &map_x, &step_x, &side);
		else 
			if_side_y(&side_dist_y, &delta_dist_y, &map_y, &step_y, &side);
		if (game->map->map[map_y][map_x] == 1) 
			hit = 1;
	}
	return (*side == 0) ? (map_x - game->player->x + (1 - step_x) / 2) / ray_dir_x
						: (map_y - game->player->y + (1 - step_y) / 2) / ray_dir_y;
}

void if_loop(int tex_x, int tex_y, t_game *game, int *color)
{
	if (tex_x < 0)// Clamp tex_x and tex_y to be within texture bounds
		tex_x = 0;
	if (tex_x >= game->wall_texture->width) 
		tex_x = game->wall_texture->width - 1;
	if (tex_y < 0) 
		tex_y = 0;
	if (tex_y >= game->wall_texture->height) 
		tex_y = game->wall_texture->height - 1;
	if (!game->wall_texture->data) // Safety check: Ensure texture data is valid
	{
		fprintf(stderr, "Texture data is NULL at draw_wall\n");
		exit(EXIT_FAILURE);
	}
	*color = ((int *)game->wall_texture->data)[tex_y * (game->wall_texture->size_line / 4) + tex_x];// Get the color from the texture
}

void draw_wall(int x, int wall_height, int side, t_game *game) 
{
	int draw_start;
	int draw_end;
	int color;
    int tex_x;
	int tex_y;

	draw_start = -wall_height / 2 + HEIGHT / 2;
    if (draw_start < 0) 
		draw_start = 0;
    draw_end = wall_height / 2 + HEIGHT / 2;
    if (draw_end >= HEIGHT) 
		draw_end = HEIGHT - 1;
    if (wall_height > HEIGHT)    // Clamp wall height to prevent extremely large values
        wall_height = HEIGHT;
    while (draw_start < draw_end)
	{
        tex_y = (draw_start - (-wall_height / 2 + HEIGHT / 2)) * game->wall_texture->height / wall_height;// Calculate texture Y-coordinate
        tex_x = (x * game->wall_texture->width) / WIDTH;// Calculate texture X-coordinate based on screen X
		if_loop(tex_x, tex_y, game, &color);
        ((int *)game->mlx_data->data)[draw_start * WIDTH + x] = color;        // Draw the pixel
        draw_start++;
    }
}

void render(t_game *game) 
{
    int		x;
	float	ray_angle;
	float	ray_dir_x;
	float	ray_dir_y;
    int		side;
	float	distance;
	int		wall_height;

	x = 0;
    clear_screen(game->mlx_data, FLOOR_COLOR);
    while (x < WIDTH) 
	{
    	ray_angle = game->player->angle - (FOV / 2) + (x * (FOV / (float)WIDTH));
        calculate_ray_direction(ray_angle, &ray_dir_x, &ray_dir_y);
        distance = perform_dda(ray_dir_x, ray_dir_y, game, &side);
        if (distance > MAX_DISTANCE) 
			distance = MAX_DISTANCE;
        wall_height = (int)(HEIGHT / distance);
        draw_wall(x, wall_height, side, game);
        x++;
    }
}
