/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:32:49 by rkrechun          #+#    #+#             */
/*   Updated: 2024/09/02 16:09:40 by rkrechun         ###   ########.fr       */
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



typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map2d;
	int		map_width;
	int		map_height;
	int		p_x;
	int		p_y;
	int		key_press;
	void	*img;
}				t_game;

char	*get_next_line(int fd);
void open_file(char *map_path, t_game *dat);
void player_position(t_game *dat);
void	*ft_calloc(size_t count, size_t size);
char ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
int ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void maps_checker(t_game *dat);
void image_in_map(t_game *game);
void	ft_bzero(void *s, size_t n);

#endif
