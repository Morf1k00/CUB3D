/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:22:42 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/22 14:50:56 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        return 1;
    else
        return 0;
}

char *ft_strtrim(char *str)
{
    char *end;

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

void check_wall_texture(t_data *data, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		data->wall_texture[0].path = ft_strdup(ft_strtrim(line + 3));
	else if (line[0] == 'S' && line[1] == 'O')
		data->wall_texture[1].path = ft_strdup(ft_strtrim(line + 3));
	else if (line[0] == 'W' && line[1] == 'E')
		data->wall_texture[2].path = ft_strdup(ft_strtrim(line + 3));
	else if (line[0] == 'E' && line[1] == 'A')
		data->wall_texture[3].path = ft_strdup(ft_strtrim(line + 3));
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
		if (line[0] == 'F' || line[0] == 'C')
			check_floor_ceiling_color(data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}