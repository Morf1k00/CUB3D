/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rewrite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:39:36 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/29 15:39:54 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	count_tabs(char *line)
{
	int count;

	count = 0;
	while (*line)
	{
		if (*line == '\t')
			count += 3;
		line++;
	}
	return(count);
} 

void map_rewrite(t_data *data)
{
	int y;
	int x;
	int z;
	char *line;
	int tabs;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		z = 0;
		tabs = count_tabs(data->map[y]);
		line = (char *)malloc(sizeof(char) * (data->map_width + tabs + 1));
		if (!line)
			return;
		while (z < data->map_width - 1)
		{
			if (data->map[y][x] && data->map[y][x] != '\n' && data->map[y][x] != '\0')
			{
				if (data->map[y][x] == ' ')
				{
					line[z++] = '0';
					x++;
				}
				else if (data->map[y][x] == '\t')
				{
					line[z++] = '0';
					line[z++] = '0';
					line[z++] = '0';
					line[z] = '0';
					x++; 
				}
				else
					line[z++] = data->map[y][x++];
			}
			else
				line[z++] = '0';
		}
		line[z++] = '\n';
		line[z++] = '\0';
		free(data->map[y]);
		data->map[y] = strdup(line);
		free(line);
		y++;
	}
}