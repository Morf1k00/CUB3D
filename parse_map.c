/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:18:11 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/30 21:14:34 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	count_width(char *line, t_data *dat)
{
	int	i;
	int	j;

	i = ft_strlen(line);
	j = count_tabs(line);
	if (i > dat->map_width)
		dat->map_width = i + j;
}

void	count_line(char *map_path, t_data *dat)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCan't open file\n");
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '1' || line[0] == '0' || line[0] == ' '
			|| line[0] == '\t')
		{
			count_width(line, dat);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	dat->map_height = i;
}

void	*ft_memset(void *b, int c, size_t len)
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

/* void	open_file(char *map_path, t_data *dat)
{
	int		fd;
	char	*line;
	int		i;
	char	*new_line;

	i = 0;
	count_line(map_path, dat);
	fd = open(map_path, O_RDONLY);
	printf("%i\n", dat->map_height);
	dat->map = malloc(sizeof(char *) * (dat->map_height + 1));
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '1' || line[0] == '0' || line[0] == ' '
			|| line[0] == '\t')
		{
			dat->map[i] = ft_strdup(line);
			i++;
			free(line);
			line = get_next_line(fd);
		}
		else
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	dat->map[i] = NULL;
	close(fd);
} */
/* 
	The open_file function in your cub3D project is responsible for opening a 
	map file, reading its contents, and storing the relevant lines in the 
	dat->map array. - refacktored by 3010 roi
 */
void	open_file(char *map_path, t_data *dat)
{
	int		fd;
	char	*line;
	int		i;

	count_line(map_path, dat);
	fd = open(map_path, O_RDONLY);
	printf("%i\n", dat->map_height);
	dat->map = malloc(sizeof(char *) * (dat->map_height + 1));
	if (!dat->map)
		return ;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '1' || line[0] == '0' || line[0] == ' '
			|| line[0] == '\t')
			dat->map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	dat->map[i] = NULL;
	close(fd);
}

/* void	check_pos(t_data *data, int i, int j)
{
	if (data->map[i][j] == 'S')
		data->player_angle = 0;
	if (data->map[i][j] == 'W')
		data->player_angle = 90;
	if (data->map[i][j] == 'E')
		data->player_angle = 180;
	if (data->map[i][j] == 'N')
		data->player_angle = 270;
} */

void	change_pos(t_data *data, int i, int j)
{
	if (data->map[i][j - 1] == '1')
		data->player_x = (float)j + 0.5;
	else
		data->player_x = (float)j;
	if (data->map[i - 1][j] == '1')
		data->player_y = (float)i + 0.5;
	else
		data->player_y = (float)i;
}

/* void	player_position(t_data *dat)
{
	int	i;
	int	j;

	i = 0;
	while (i < dat->map_height)
	{
		j = 0;
		while (dat->map[i][j])
		{
			if (dat->map[i][j] == 'N' || dat->map[i][j] == 'S' ||
				dat->map[i][j] == 'W' || dat->map[i][j] == 'E')
			{
				// check_pos(dat, i, j);
				change_pos(dat, i, j);
				dat->player_x = (float)j + 0.5;
				dat->player_y = (float)i + 0.5;
				dat->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
	if (i == dat->map_height)
	{
		printf("Error\nNo player position\n");
		return ;
	}
} */
/* 
	The  function  is responsible for finding the initial position of the player
	on the map, setting the player's coordinates, and updating the map to
	reflect the player's starting position.  
		- refacktored by 3010 roi
*/
void	player_position(t_data *dat)
{
	int	i;
	int	j;

	i = -1;
	while (++i < dat->map_height)
	{
		j = -1;
		while (dat->map[i][++j])
		{
			if (dat->map[i][j] == 'N' || dat->map[i][j] == 'S' ||
				dat->map[i][j] == 'W' || dat->map[i][j] == 'E')
			{
				change_pos(dat, i, j);
				dat->player_x = (float)j + 0.5;
				dat->player_y = (float)i + 0.5;
				dat->map[i][j] = '0';
				return ;
			}
		}
	}
	if (i == dat->map_height)
		printf("Error\nNo player position\n");
}
