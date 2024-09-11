/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:18:11 by rkrechun          #+#    #+#             */
/*   Updated: 2024/09/04 14:09:51 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libc/cub3d.h"

void	count_width(char *line, t_game *dat)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i > dat->map_width)
		dat->map_width = i;
	
}

void	count_line(char *map_path, t_game *dat)
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
		count_width(line, dat);
		i++;
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
	memset(new_line + old_len - 1, '0', padding_len);
	new_line[width - 1] = '\n';
	new_line[width] = '\0';
	return (new_line);
}

void	open_file(char *map_path, t_game *dat)
{
	int		fd;
	char	*line;
	int		i;
	char *new_line;

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
		if (ft_strlen(line) < dat->map_width)
		{	
			new_line = line_bigger(line, dat->map_width);
			dat->map2d[i] = ft_strdup(new_line);
			free(new_line);
		}
		else
			dat->map2d[i] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	dat->map2d[i] = NULL;
	close(fd);
}

void	maps_checker(t_game *dat)
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
		i++;
	}
}

void	player_position(t_game *dat)
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
				dat->ray->player_x = j;
				dat->ray->player_y = i;
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
