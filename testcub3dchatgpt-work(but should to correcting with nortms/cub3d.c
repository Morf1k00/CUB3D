// gcc cub3d.c -I~/minilibx -L~/minilibx -lmlx -lX11 -lXext -lm -o cub3d

#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1260         // Ширина окна в пикселях
#define HEIGHT 800        // Высота окна в пикселях
#define FOV 60            // Поле зрения (угол обзора) в градусах
#define MAP_WIDTH 5       // Ширина карты в тайлах
#define MAP_HEIGHT 5      // Высота карты в тайлах
#define TILE_SIZE 64     // Размер одного тайла в пикселях
#define PLAYER_RADIUS 5  // Радиус игрока в пикселях
#define M_PI 3.14159265358979323846 // Значение числа π (пи)
#define FLOOR_COLOR 0x000000
#define MAX_DISTANCE 100 // Максимальное расстояние для прорисовки
#define MOVE_SPEED 0.1  // Скорость движения игрока
#define ROTATION_SPEED 3  // Скорость поворота в градусах

// Упрощенная карта (1 = стена, 0 = пустое место)
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1}
};

// Позиция игрока
float player_x = 2.5; // Центр тайла
float player_y = 1.5; // Центр тайла
float player_angle = 90; // Угол направления игрока

// Структура для данных MLX
typedef struct {
    void *mlx;
    void *win;
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
} t_data;

// Структура для текстуры
typedef struct {
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
    int width;   // Ширина текстуры
    int height;  // Высота текстуры
} t_texture;

t_texture wall_texture; // Текстура для стен
t_texture floor_texture; // Текстура для пола

// Функция для загрузки текстуры
void load_texture(t_data *data, t_texture *texture, const char *file_path) {
    texture->img = mlx_xpm_file_to_image(data->mlx, (char *)file_path, &texture->width, &texture->height);
    if (!texture->img) {
        fprintf(stderr, "Failed to load texture: %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
}

// Функция для очистки экрана определенным цветом
void clear_screen(t_data *data, int color) {
    int x = 0;
    int y = 0;
    while (y < HEIGHT) {
        while (x < WIDTH) {
            ((int *)data->data)[y * WIDTH + x] = color;
            x++;
        }
        x = 0;
        y++;
    }
}

// Функция для отрисовки сцены
void render(t_data *data)
{
    clear_screen(data, FLOOR_COLOR); // Очистить экран (черный пол)

    int x = 0;
    while (x < WIDTH)
    {
        // Рассчитать угол луча относительно игрока
        float ray_angle = player_angle - (FOV / 2) + (x * (FOV / (float)WIDTH));
        // Преобразовать ray_angle из градусов в радианы
        float ray_angle_rad = ray_angle * M_PI / 180.0;
        // Направление луча
        float ray_dir_x = cos(ray_angle_rad);
        float ray_dir_y = sin(ray_angle_rad);
        // Переменные для шага и расчета расстояний
        float delta_dist_x = fabs(1 / ray_dir_x);
        float delta_dist_y = fabs(1 / ray_dir_y);
        int map_x = (int)player_x;
        int map_y = (int)player_y;
        float side_dist_x;
        float side_dist_y;
        int step_x;
        int step_y;
        int hit = 0;
        int side; // 0 для вертикальной стены, 1 для горизонтальной стены
        // Рассчитать шаг и начальное side_dist
        if (ray_dir_x < 0) 
        {
            step_x = -1;
            side_dist_x = (player_x - map_x) * delta_dist_x;
        }
        else 
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - player_x) * delta_dist_x;
        }
        if (ray_dir_y < 0) 
        {
            step_y = -1;
            side_dist_y = (player_y - map_y) * delta_dist_y;
        } 
        else 
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - player_y) * delta_dist_y;
        }
        // Выполнить DDA (Цифровой дифференциальный анализ) для определения стен
        while (!hit)
        {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (map[map_y][map_x] == 1) hit = 1; // Стена найдена
        }
        // Рассчитать расстояние до стены
        float perp_wall_dist;
        if (side == 0) perp_wall_dist = (map_x - player_x + (1 - step_x) / 2) / ray_dir_x;
        else perp_wall_dist = (map_y - player_y + (1 - step_y) / 2) / ray_dir_y;
        // Ограничить расстояние до MAX_DISTANCE
        if (perp_wall_dist > MAX_DISTANCE) perp_wall_dist = MAX_DISTANCE;
        // Рассчитать высоту стены на основе расстояния
        int wall_height = (int)(HEIGHT / perp_wall_dist);
        // Рассчитать, где начинать и заканчивать отрисовку стены
        int draw_start = -wall_height / 2 + HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = wall_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;
        // Отрисовка текстуры на стене
        for (int y = draw_start; y < draw_end; y++) {
            int tex_y = (y - draw_start) * wall_texture.height / (draw_end - draw_start);
            int tex_x = (x * wall_texture.width) / WIDTH;
            // Получить цвет из текстуры
            int color = ((int *)wall_texture.data)[tex_y * (wall_texture.size_line / 4) + tex_x];
            // Нарисовать пиксель
            ((int *)data->data)[y * WIDTH + x] = color;
        }
        x++;
    }
}

// Обработка нажатий клавиш для вращения и движения
int handle_key_press(int keycode, t_data *data) {
    if (keycode == 65307) {  // Клавиша Escape на Linux
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    if (keycode == 65361) {  // Левая стрелка (поворот влево)
        player_angle -= 5;  // Повернуть влево на 5 градусов
        if (player_angle < 0) player_angle += 360;  // Обертка если нужно
        render(data);  // Перерисовать сцену после поворота
    }
    if (keycode == 65363) {  // Правая стрелка (поворот вправо)
        player_angle += 5;  // Повернуть вправо на 5 градусов
        if (player_angle >= 360) player_angle -= 360;  // Обертка если нужно
        render(data);  // Перерисовать сцену после поворота
    }
    if (keycode == 65362) {  // Верхняя стрелка (движение вперед)
        // Рассчитать вектор направления на основе player_angle
        float move_x = cos(player_angle * M_PI / 180.0) * MOVE_SPEED;
        float move_y = sin(player_angle * M_PI / 180.0) * MOVE_SPEED;
        // Проверить столкновение перед движением
        if (map[(int)(player_y + move_y)][(int)(player_x + move_x)] == 0) {
            player_x += move_x;
            player_y += move_y;
        }
        render(data);  // Перерисовать сцену после движения
    }
    if (keycode == 65364) {  // Нижняя стрелка (движение назад)
        // Рассчитать вектор направления на основе player_angle
        float move_x = cos(player_angle * M_PI / 180.0) * MOVE_SPEED;
        float move_y = sin(player_angle * M_PI / 180.0) * MOVE_SPEED;
        // Проверить столкновение перед движением
        if (map[(int)(player_y - move_y)][(int)(player_x - move_x)] == 0) {
            player_x -= move_x;
            player_y -= move_y;
        }
        render(data);  // Перерисовать сцену после движения
    }
    return 0;
}

// Функция для непрерывного рендеринга и обработки событий
int game_loop(t_data *data) {
    render(data);  // Рендеринг сцены
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);  // Отобразить изображение в окне
    return 0;
}

int main() {
    t_data data;
    // Инициализация MLX
    data.mlx = mlx_init();
    if (!data.mlx) {
        fprintf(stderr, "Failed to initialize MLX\n");
        return EXIT_FAILURE;
    }
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
    if (!data.win) {
        fprintf(stderr, "Failed to create window\n");
        return EXIT_FAILURE;
    }
    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    if (!data.img) {
        fprintf(stderr, "Failed to create image\n");
        return EXIT_FAILURE;
    }
    data.data = mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endian);
    if (!data.data) {
        fprintf(stderr, "Failed to get image data address\n");
        return EXIT_FAILURE;
    }
    // Загрузить текстуры
    load_texture(&data, &wall_texture, "wall.xpm"); // Одна текстура для всех стен
    // Зарегистрировать обработчик нажатий клавиш
    mlx_hook(data.win, 2, 1L << 0, handle_key_press, &data);  // 2 - событие нажатия клавиши
    // Зарегистрировать игровой цикл для непрерывного рендеринга и обработки событий
    mlx_loop_hook(data.mlx, game_loop, &data);
    // Запустить цикл событий
    mlx_loop(data.mlx);
    // Очистка
    mlx_destroy_image(data.mlx, data.img);
    mlx_destroy_window(data.mlx, data.win);
    mlx_destroy_display(data.mlx);
    free(data.mlx);
    return 0;
}
