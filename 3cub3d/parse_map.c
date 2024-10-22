/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:18:11 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/22 17:18:16 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	count_width(char *line, t_data *dat)
{
	int	i;

	i = ft_strlen(line);
	if (i > dat->map_width)
		dat->map_width = i;
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
		if (line[0]== '1' || line[0] == '0' || line[0] == ' ' || line[0] == '\t')
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

char *line_bigger(char *line, int width)
{
    int old_len;
    int padding_len;
    char *new_line;

	old_len = ft_strlen(line);
	padding_len = width - old_len;
	new_line = malloc(sizeof(char) * (width + 1));
	if (!new_line)
		return (NULL);
	strncpy(new_line, line, old_len - 1);
	memset(new_line + old_len - 1, '1', width - old_len);
	new_line[width - 1] = '\n';
	new_line[width] = '\0';
	return (new_line);
}

void	open_file(char *map_path, t_data *dat)
{
	int		fd;
	char	*line;
	int		i;
	char *new_line;

	i = 0;
	count_line(map_path, dat);
	fd = open(map_path, O_RDONLY);
	dat->map = malloc(sizeof(char *) * (dat->map_height + 1));
	line = get_next_line(fd);
	while (line)	
	{
		if (line[0]== '1' || line[0] == '0' || line[0] == ' ' || line[0] == '\t')
		{
			if (ft_strlen(line) < dat->map_width)
			{	
				new_line = line_bigger(line, dat->map_width);
				dat->map[i] = ft_strdup(new_line);
				free(new_line);
			}
			else
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
}

void check_pos(t_data *data, int i, int j)
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

void change_pos(t_data *data, int i, int j)
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

void	player_position(t_data *dat)
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
				check_pos(dat, i, j);
				change_pos(dat, i, j);
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
}
