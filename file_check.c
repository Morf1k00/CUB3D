/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:22:42 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/07 14:44:44 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	else
		return (0);
}

char	*ft_strtrim1(char *str)
{
	char	*end;

	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return (ft_strdup(""));
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}

void	check_wall_texture(t_data *data, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		data->wall_texture[0].path = ft_strdup(ft_strtrim1(line + 3));
	else if (line[0] == 'S' && line[1] == 'O')
		data->wall_texture[1].path = ft_strdup(ft_strtrim1(line + 3));
	else if (line[0] == 'W' && line[1] == 'E')
		data->wall_texture[2].path = ft_strdup(ft_strtrim1(line + 3));
	else if (line[0] == 'E' && line[1] == 'A')
		data->wall_texture[3].path = ft_strdup(ft_strtrim1(line + 3));
}

/* void	check_wall_texture(t_data *data, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		data->wall_texture[0].path = ft_strdup(ft_strtrim(line + 3, " "));
	else if (line[0] == 'S' && line[1] == 'O')
		data->wall_texture[1].path = ft_strdup(ft_strtrim(line + 3, " "));
	else if (line[0] == 'W' && line[1] == 'E')
		data->wall_texture[2].path = ft_strdup(ft_strtrim(line + 3, " "));
	else if (line[0] == 'E' && line[1] == 'A')
		data->wall_texture[3].path = ft_strdup(ft_strtrim(line + 3, " "));
} */

void	check_floor_ceiling_color(t_data *data, char *line)
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
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
}

void	finder_coordinate(t_data *data, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		prog_exit(FILE_OPEN, data, 1);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'N' || line[0] == 'S'
			|| line[0] == 'W' || line[0] == 'E')
			check_wall_texture(data, line);
		if (line[0] == 'F' || line[0] == 'C')
			check_floor_ceiling_color(data, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
