/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tabs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:30:00 by oruban            #+#    #+#             */
/*   Updated: 2024/11/07 16:17:12 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
/* 
	refacturing after shortening map_rewrite() it was devieded into 5
	functionsthere fore count_tabs() had to be removed file 
	map_rewrite.c into the ceperated file count_tabs.c 
		refactured by roi 1103
 */
int	count_tabs(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == '\t')
			count += 3;
		line++;
	}
	return (count);
}

void	check_pos(t_data *data, int i, int j)
{
	if (data->map[i][j] == 'S')
		data->player_angle = 0;
	if (data->map[i][j] == 'W')
		data->player_angle = 90;
	if (data->map[i][j] == 'E')
		data->player_angle = 180;
	if (data->map[i][j] == 'N')
		data->player_angle = 270;
}

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

void	check_file(char *path)
{
	char	*way;
	int		i;
	int		l;

	way = ".cub";
	i = 4;
	l = ft_strlen(path);
	while (i > 0)
	{
		if (path[l] == way[i])
		{
			l--;
			i--;
		}
		else
			simple_exit(WRONG_PATH);
	}
}
