/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:00:20 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/07 16:17:41 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	free_map(char **map_copy)
{
	int	i;

	i = 0;
	while (map_copy[i] != NULL)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

char	**copy_map(char **map)
{
	int		height;
	char	**map_copy;
	int		i;

	height = 0;
	while (map[height] != NULL)
		height++;
	map_copy = malloc((height + 1) * sizeof(char *));
	if (!map_copy)
		prog_exit(MEMORY_ALLOC, NULL, 1);
	i = -1;
	while (++i < height)
	{
		map_copy[i] = strdup(map[i]);
		if (!map_copy[i])
		{
			free_map(map_copy);
			prog_exit(MEMORY_ALLOC, NULL, 1);
		}
	}
	return (map_copy[height] = NULL, map_copy);
}

int	f_fill(t_data *data, int p_y, int p_x)
{
	int	c_x;
	int	c_y;

	c_x = p_x;
	c_y = p_y;
	if (c_y >= data->map_height || c_x >= data->map_width)
		prog_exit(ERORR_CLOSE, data, 1);
	if (c_y < 0 || c_x < 0 || data->map[c_y][c_x] == '1'
		|| data->map[c_y][c_x] == 'F')
		return (0);
	data->map[c_y][c_x] = 'F';
	if (f_fill(data, c_y + 1, c_x) || f_fill(data, c_y - 1, c_x)
		|| f_fill(data, c_y, c_x + 1) || f_fill(data, c_y, c_x - 1))
		return (1);
	return (0);
}
/* 
	the function checks if the map in a game is closed or not.
	refactured by roi 1101
 */

void	check_walls(t_data *data)
{
	char		**map;
	int			y;
	int			x;

	y = (int)data->player_y;
	x = (int)data->player_x;
	if (f_fill(data, y, x))
		prog_exit("MAP_CLOSE", data, 1);
}
