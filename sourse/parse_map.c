/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:18:11 by rkrechun          #+#    #+#             */
/*   Updated: 2024/08/28 17:33:27 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libc/cub3d.h"

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
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	dat->map_height = i;
	printf("%d\n", i);
}

void	count_width(char *line, t_data *dat)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i > dat->map_width)
		dat->map_width = i;
}

void	open_file(char *map_path, t_data *dat)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	count_line(map_path, dat);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCan't open file\n");
		return ;
	}
	dat->map2d = malloc(sizeof(char *) * (dat->map_height + 1));
	line = get_next_line(fd);
	while (line)
	{
		count_width(line, dat);
		printf("map_width = %d\n", dat->map_width);
		dat->map2d[i] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	maps_checker(t_data *dat)
{
	int	i;
	int	j;

	i = 0;
	while (i < dat->map_height)
	{
		j = 0;
		while (dat->map2d[i][j])
		{
			if (dat->map2d[i][j] == ' ')
			{
				dat->map2d[i][j] = '0';
			}
			j++;
		}
		printf("%s", dat->map2d[i]);
		i++;
	}
}

void	player_position(t_data *dat)
{
	int	i;
	int	j;

	i = 0;
	while (i < dat->map_height)
	{
		j = 0;
		while (dat->map2d[i][j])
		{
			if (dat->map2d[i][j] == 'N' || dat->map2d[i][j] == 'S'
					|| dat->map2d[i][j] == 'W' || dat->map2d[i][j] == 'E')
			{
				dat->p_x = j;
				dat->p_y = i;
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
}
