/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:18:11 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/08 15:53:09 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

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
		prog_exit(FILE_OPEN, dat, 1);
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

void	open_file(char *map_path, t_data *dat)
{
	int		fd;
	char	*line;
	int		i;

	count_line(map_path, dat);
	fd = open(map_path, O_RDONLY);
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
				check_pos(dat, i, j);
				dat->player_x = (float)j + 0.5;
				dat->player_y = (float)i + 0.5;
				dat->map[i][j] = '0';
				return ;
			}
		}
	}
	if (i == dat->map_height)
		prog_exit(PLAYER_EXIST, dat, 1);
}
