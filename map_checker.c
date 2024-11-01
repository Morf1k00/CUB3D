/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:00:20 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/01 16:44:36 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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

/* char	**copy_map(char **map)
{
	int		height;
	char	**map_copy;
	int		i;

	height = 0;
	while (map[height] != NULL)
		height++;
	map_copy = malloc((height + 1) * sizeof(char *));
	if (!map_copy)
	{
		perror("Failed to allocate memory for map copy");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < height)
	{
		map_copy[i] = strdup(map[i]);
		if (!map_copy[i])
		{
			perror("Failed to allocate memory for map row");
			free_map(map_copy);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	map_copy[height] = NULL;
	return (map_copy);
} */

/* 
	The function creates a deep copy of a 2D array of strings (a map).
	refactured by roi 1101
 */
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
	{
		perror("Failed to allocate memory for map copy");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < height)
	{
		map_copy[i] = strdup(map[i]);
		if (!map_copy[i])
		{
			perror("Failed to allocate memory for map row");
			free_map(map_copy);
			exit(EXIT_FAILURE);
		}
	}
	return (map_copy[height] = NULL, map_copy);
}

void	exit_program(char *error)
{
	printf("Error\n%s\n", error);
	exit(1);
}

/* int	f_fill(int h, int w, char **map, int p_y, int p_x)
{
	int	c_x;
	int	c_y;

	c_x = p_x;
	c_y = p_y;
	if (c_y >= h || c_x >= w)
		exit(0);
	if (c_y < 0 || c_x < 0 || map[c_y][c_x] == '1' || map[c_y][c_x] == 'F')
		return (0);
	map[c_y][c_x] = 'F';
	if (f_fill(h, w, map, c_y + 1, c_x) || f_fill(h, w, map, c_y - 1, c_x)
		|| f_fill(h, w, map, c_y, c_x + 1) || f_fill(h, w, map, c_y, c_x - 1))
		return (1);
	return (0);
}

void	check_walls(t_data *data)
{
	char	**map;
	int		y;
	int		x;
	int		h;
	int		w;

	y = (int)data->player_y;
	x = (int)data->player_x;
	h = data->map_height;
	w = data->map_width;
	map = copy_map(data->map);
	if (!f_fill(h, w, map, y, x))
		printf("Map is closed\n");
	else
		printf("Map is not closed\n");
} */

/* 
 	function is a recursive flood fill algorithm that fills a region in a 2D map
	with a specific character ('F'). refactured by roi 1101
*/
int	f_fill(t_map_data *map_data, int p_y, int p_x)
{
	int	c_x;
	int	c_y;

	c_x = p_x;
	c_y = p_y;
	if (c_y >= map_data->height || c_x >= map_data->width)
		exit(0);
	if (c_y < 0 || c_x < 0 || map_data->map[c_y][c_x] == '1'
		|| map_data->map[c_y][c_x] == 'F')
		return (0);
	map_data->map[c_y][c_x] = 'F';
	if (f_fill(map_data, c_y + 1, c_x) || f_fill(map_data, c_y - 1, c_x)
		|| f_fill(map_data, c_y, c_x + 1) || f_fill(map_data, c_y, c_x - 1))
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
	t_map_data	map_data;

	y = (int)data->player_y;
	x = (int)data->player_x;
	map_data.height = data->map_height;
	map_data.width = data->map_width;
	map_data.map = copy_map(data->map);
	if (!f_fill(&map_data, y, x))
		printf("Map is closed\n");
	else
		printf("Map is not closed\n");
}
