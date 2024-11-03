/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rewrite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:39:36 by rkrechun          #+#    #+#             */
/*   Updated: 2024/11/01 22:06:36 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	count_tabs(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == '\t')
			count += 3;
		line++;
	}
	return (count);
}

/* 
	The function rewrites the map in the game data structure, replacing spaces
	with '0' characters and tabs with '0000' sequences. Refactured by roi 1101
*/
void	map_rewrite(t_data *data)
{
	int		y;
	int		x;
	int		z;
	char	*line;
	int		tabs;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		z = 0;
		tabs = count_tabs(data->map[y]);
		line = (char *)malloc(sizeof(char) * (data->map_width + tabs + 1));
		if (!line)
			return ;
		while (z < data->map_width - 1)
		{
			if (data->map[y][++x] && data->map[y][x] != '\n'
				&& data->map[y][x] != '\0')
			{
				if (data->map[y][x] == ' ')
					line[z++] = '0';
				else if (data->map[y][x] == '\t')
				{
					line[z++] = '0';
					line[z++] = '0';
					line[z++] = '0';
					line[z] = '0';
				}
				else
					line[z++] = data->map[y][x];
			}
			else
				line[z++] = '0';
		}
		line[z++] = '\n';
		line[z++] = '\0';
		free(data->map[y]);
		data->map[y] = strdup(line);
		free(line);
	}
}

/* #include "game.h"
#include <stdlib.h>
#include <string.h>

// Rewrites the map, replacing spaces with '0' and tabs with "0000".
 
void map_rewrite(t_data *data) {
    for (int y = 0; y < data->map_height; y++) {
		
        // Calculate the size of the new line, accounting for tab expansion.
        size_t new_len = strlen(data->map[y]) + 3 * count_tabs(data->map[y]);

        // Allocate memory for the new line.  Using calloc initializes the memory to 0,
        // simplifying the logic later.
        char *new_line = calloc(new_len + 1, sizeof(char)); // +1 for null terminator
        if (!new_line) {
            // Handle allocation failure.  Consider exiting or returning an error.
            perror("Memory allocation failed");
            exit(EXIT_FAILURE); // or return an error code
        }

        size_t new_index = 0;
        for (size_t old_index = 0; data->map[y][old_index] != '\0'; old_index++) {
            char c = data->map[y][old_index];
            if (c == ' ') {
                new_line[new_index++] = '0';
            } else if (c == '\t') {
                strcat(new_line + new_index, "0000"); // Use strcat for efficiency.
                new_index += 4;
            }
            else if (c != '\n') {
                new_line[new_index++] = c;
            } // we implicitly skip '\n' since calloc initialized with 0 and we append '\n' later

        }
        new_line[new_index] = '\n';


        free(data->map[y]);
        data->map[y] = new_line;
    }
} */