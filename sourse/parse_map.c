/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:18:11 by rkrechun          #+#    #+#             */
/*   Updated: 2024/08/27 17:01:13 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libc/cub3d.h"

void parse_map(t_data *dat)
{
	int i;
	int j;

	i = 0;
	while (dat->map2d[i])
	{
		j = 0;
		while (dat->map2d[i][j])
		{
			if (dat->map2d[i][j] == '1' || dat->map2d[i][j] == '2'
				|| dat->map2d[i][j] == 'N' || dat->map2d[i][j] == 'S'
				|| dat->map2d[i][j] == 'W' || dat->map2d[i][j] == 'E')
				j++;
			else if (dat->map2d[i][j] == ' ')
			{
				dat->map2d[i][j] = '0';
				j++;
			}
		}
		i++;
	}
	dat->map_height = i;
}
 
void parse_wigth(t_data *dat)
{
	int i;
	int k;
	int j;

	i = 0;
	k = 0;
	while (dat->map2d[i])
	{
		j = 0;
		while(dat->map2d[i][j] != '\0')
			j++;
		if (j > k)
			k = j;
		i++;
	}
	dat->map_width = k;
}

void player_position(t_data *dat)
{
	int i;
	int j;

	i = 0;
	while (dat->map2d[i])
	{
		j = 0;
		while (dat->map2d[i][j])
		{
			if (dat->map2d[i][j] == 'P')
			{
				dat->p_x = j;
				dat->p_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
	if (dat->map2d[i] == NULL)
	{
		printf("Error\nNo player position\n");
		return ;
	}
}

