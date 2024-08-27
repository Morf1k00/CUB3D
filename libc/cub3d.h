/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:32:49 by rkrechun          #+#    #+#             */
/*   Updated: 2024/08/27 15:40:46 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include <math.h>
# include <string.h>

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
