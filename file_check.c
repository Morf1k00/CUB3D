/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:22:42 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/16 16:54:43 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void check_wall_texture(t_data *data, char *line)
{
	if (line[0] == 'N')
		data->north_texture = ft_strdup(line + 2);
	else if (line[0] == 'S')
		data->south_texture = ft_strdup(line + 2);
	else if (line[0] == 'W')
		data->west_texture = ft_strdup(line + 2);
	else if (line[0] == 'E')
		data->east_texture = ft_strdup(line + 2);
}

void check_floor_ceiling_color(t_data *data, char *line)
{
	int		i;
	int		color;
	char	**rgb;

	i = 0;
	while (line[i] != ' ')
		i++;
	rgb = ft_split(line + i, ',');
	color = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]);
	if (line[0] == 'F')
		data->color_f = color;
	else if (line[0] == 'C')
		data->color_c = color;
}

void finder_coordinate(t_data *data, char *file_name)
{
	int fd;
	char *line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCan't open file\n");
		return ;
	}
	line = get_next_line(fd);
	while(line)
	{
		if (line[0] =='N' || line[0] == 'S'
			|| line[0] == 'W' || line[0] == 'E')
			check_wall_texture(data, line);
		else if (line[0] == 'F' || line[0] == 'C')
			check_floor_ceiling_color(data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}