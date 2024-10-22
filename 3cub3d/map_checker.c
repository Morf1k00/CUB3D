/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:00:20 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/22 16:25:27 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void error_exit(const char *message)
{
    printf("Error: %s\n", message);
    exit(EXIT_FAILURE);
}

bool is_wall_or_space(char c)
{
    return (c == '1' || ft_isspace(c));
}

bool check_surroundings(t_data *data, int y, int x)
{
    if (y <= 0 || x <= 0 || y >= data->map_height - 1 || x >= data->map_width - 1)
        return false;

    return (is_wall_or_space(data->map[y][x - 1]) &&
            is_wall_or_space(data->map[y][x + 1]) &&
            is_wall_or_space(data->map[y - 1][x]) &&
            is_wall_or_space(data->map[y + 1][x]));
}

// Check that the map is closed on top and bottom
bool check_top_bottom(t_data *data)
{
    int i = 0;
    while (i < data->map_width)
    {
        if (data->map[0][i] != '1' && !ft_isspace(data->map[0][i]))
            return false;
        if (data->map[data->map_height - 1][i] != '1' && !ft_isspace(data->map[data->map_height - 1][i]))
            return false;
        i++;
    }
    return true;
}

// Check left and right sides of each row
bool check_left_right(t_data *data)
{
    int i = 0;
    while (i < data->map_height)
    {
        int first_non_space = 0;
        while (ft_isspace(data->map[i][first_non_space]))
            first_non_space++;
        if (data->map[i][first_non_space] != '1')
            return false;

        int last_non_space = ft_strlen(data->map[i]) - 1;
        while (last_non_space > 0 && ft_isspace(data->map[i][last_non_space]))
            last_non_space--;
        if (data->map[i][last_non_space] != '1')
            return false;

        i++;
    }
    return true;
}

// Ensure that the map is fully enclosed by walls
bool is_map_closed(t_data *data)
{
    return check_top_bottom(data) && check_left_right(data);
}

void check_map_chars(t_data *data)
{
    int y;
    int player_count;
	char cell;
	int x;

	y = 0;
	player_count = 0;
    while (y < data->map_height)
    {
        x = 0;
        while (x < ft_strlen(data->map[y]))
        {
            cell = data->map[y][x];
            if (ft_isspace(cell))
            {
                x++;
                continue;
            }
            if (strchr("NSEW", cell))
            {
                if (!check_surroundings(data, y, x))
                    error_exit("Map is not closed around player position");
                player_count++;
            }
            else if (cell == '0')
                if (!check_surroundings(data, y, x))
                    error_exit("Map is not closed around empty space");
            else if (cell != '1' && cell != ' ')
                error_exit("Invalid character in map");
            x++;
        }
        y++;
    }
    if (player_count == 0)
        error_exit("No player start position found");
    if (player_count > 1)
        error_exit("Multiple player start positions found");
}

void check_map(t_data *data)
{
    if (!is_map_closed(data))
        error_exit("Map is not closed at the boundaries");
    check_map_chars(data);
}
