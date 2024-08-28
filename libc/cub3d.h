/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:32:49 by rkrechun          #+#    #+#             */
/*   Updated: 2024/08/28 17:13:48 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct s_data
{
	char		**map2d;
	int		map_width;
	int		map_height;
	int		p_x;
	int		p_y;
	int		key_press;
}				t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_data	*dat;
	
}				t_mlx;

char	*get_next_line(int fd);
void open_file(char *map_path, t_data *dat);
void parse_map(t_data *dat);
void parse_wigth(t_data *dat);
void player_position(t_data *dat);
void	*ft_calloc(size_t count, size_t size);
char ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
int ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void maps_checker(t_data *dat);


#endif
