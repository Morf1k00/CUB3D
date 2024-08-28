/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:32:49 by rkrechun          #+#    #+#             */
/*   Updated: 2024/08/28 13:45:50 by rkrechun         ###   ########.fr       */
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

typedef struct s_data
{
	int		**map2d;
	int		map_width;
	int		map_height;
	int		p_x;
	int		p_y;
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

#endif
