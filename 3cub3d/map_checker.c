/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:00:20 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/24 14:32:19 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// void floodFill(t_data *data, int startX, int startY)
// {
//     int x = startX;
//     int y = startY;

//     if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height || data->map[y][x] != '0') 
//         return;
    

//     int stack[WIDTH * HEIGHT][2];
//     int top = -1;

//     stack[++top][0] = x;
//     stack[top][1] = y;

//     while (top >= 0)
// 	{
//         x = stack[top][0];
//         y = stack[top][1];
//         top--;
//         if (data->map[y][x] == '0')
// 		{
//             data->map[y][x] = '2';
//             if (y + 1 < data->map_height)
// 			{
//                 stack[++top][0] = x;
//                 stack[top][1] = y + 1;
//             }
//             if (y - 1 >= 0) {
//                 stack[++top][0] = x;
//                 stack[top][1] = y - 1;
//             }
//             if (x + 1 < data->map_width) {
//                 stack[++top][0] = x + 1;
//                 stack[top][1] = y;
//             }
//             if (x - 1 >= 0) {
//                 stack[++top][0] = x - 1;
//                 stack[top][1] = y;
//             }
//         }
//     }
// }

// // Функция для проверки замкнутости карты, начиная с позиции игрока
// bool isMapClosed(t_data *data, int playerX, int playerY) {
//     // Запуск Flood Fill из позиции игрока
//     if (data->map[playerY][playerX] != '0') 
//         return false; // Если позиция игрока не проходимая, карта не замкнута
    
//     floodFill(data, playerX, playerY); // Запуск Flood Fill из позиции игрока
//     // Проверяем, остались ли ещё '0'
//     for (int j = 0; j < data->map_height; j++) {
//         for (int i = 0; i < data->map_width; i++) {
//             if (data->map[j][i] == '0') {
//                 return false; // Если остались '0', карта не замкнута
//             }
//         }
//     }
//     return true; // Все клетки заполнены
// }


static int f_fill(t_data *data, char **map, int p_y, int p_x)
{
    int c_x = p_x;
    int c_y = p_y;

    // Check boundaries and invalid positions
    if (map[c_y][c_x] == '\0')
    {
		printf("Error\n");
		exit(1);
	}
    if (c_y < 0 || c_x < 0 || map[c_y][c_x] == '1' || map[c_y][c_x] == 'F')
        return 0;
    // Mark the cell as visited
    map[c_y][c_x] = 'F';

    // Recursive flood fill in all directions
    if (f_fill(data, map, c_y + 1, c_x) || f_fill(data, map, c_y - 1, c_x) || 
        f_fill(data,map, c_y, c_x + 1) || f_fill(data,map, c_y, c_x - 1))
        return 1;
    return 0;
}
   
void check_walls(t_data *data)
{

    char **map = data->map;
    if (f_fill(data,map, (int)data->player_y, (int)data->player_x))
    {
        printf("Error\n");
        exit(1);
    }
}
