/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rewrite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:39:36 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/08 15:53:00 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	handle_memory_allocation(char **line, int width_with_tabs)
{
	*line = (char *)malloc(sizeof(char) * (width_with_tabs + 1));
	if (!*line)
		exit(1);
}

void	replace_characters(t_data *data, char *line, int y, int *z)
{
	int	x;
	int	i;

	x = -1;
	while (*z < data->map_width - 1)
	{
		if (data->map[y][++x] && data->map[y][x] != '\n'
			&& data->map[y][x] != '\0')
		{
			if (data->map[y][x] == ' ')
				line[(*z)++] = '0';
			else if (data->map[y][x] == '\t')
				prog_exit(WRONG_MAP, data, 1);
			else
				line[(*z)++] = data->map[y][x];
		}
		else
			line[(*z)++] = '0';
	}
}

void	process_line(t_data *data, int y)
{
	int		z;
	int		tabs;
	char	*line;

	z = 0;
	handle_memory_allocation(&line, data->map_width);
	replace_characters(data, line, y, &z);
	line[z++] = '\n';
	line[z] = '\0';
	free(data->map[y]);
	data->map[y] = strdup(line);
	free(line);
}

void	map_rewrite(t_data *data)
{
	int	y;

	y = -1;
	while (++y < data->map_height)
		process_line(data, y);
}
