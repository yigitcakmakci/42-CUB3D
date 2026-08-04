#include "cub3d.h"
#include "cub3d_parser.h"
#include "cub3d_raycasting.h"
#include <stdio.h>

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

void init_dummy_map(t_game *game)
{
    int dummy[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
            game->map[y][x] = dummy[y][x];
    }
}

static void print_map(t_data *data)
{
    int i;

    printf("Map (%d x %d):\n", data->map_width, data->map_height);
    i = 0;
    while (i < data->map_height)
    {
        printf("%s\n", data->map[i]);
        i++;
    }
}

static void print_data(t_data *data)
{
    printf("NO: %s\n", data->no);
    printf("SO: %s\n", data->so);
    printf("WE: %s\n", data->we);
    printf("EA: %s\n", data->ea);

    printf("Floor   : %d,%d,%d\n",
        data->floor[0], data->floor[1], data->floor[2]);
    printf("Ceiling : %d,%d,%d\n",
        data->ceiling[0], data->ceiling[1], data->ceiling[2]);

    printf("Player : (%d, %d) %c\n",
        data->player_x,
        data->player_y,
        data->player_dir);

    print_map(data);
}

static int run_parser_mode(char *path)
{
    t_data data;

    ft_memset(&data, 0, sizeof(t_data));
    if (parse_file(path, &data))
    {
        printf("Error\n");
        return (1);
    }
    printf("Parsing successful!\n\n");
    print_data(&data);
    free_data(&data);
    return (0);
}

int key_hook(int keycode, t_game *game)
{
    if (keycode == KEY_A)
    {
        game->pos_x--;
    }
    if (keycode == KEY_W)
    {
        game->pos_y--;
    }
    if (keycode == KEY_S)
    {
        game->pos_y++;
    }
    if (keycode == KEY_D)
    {
        game->pos_x++;
    }

    
    return (0);
}

static int run_raycaster_demo(void)
{
    t_game game;

    game.pos_x = 1.0;
    game.pos_y = 1.0;
    game.dir_x = 1.0;
    game.dir_y = 1.0;

    init_dummy_map(&game);
    game.mlx = mlx_init();
    if (game.mlx == NULL)
    {
        printf("MLX could not be started");
        return (0);
    }
    
    if (!game.mlx)
        return (1);
    game.win = mlx_new_window(game.mlx, 800, 600, "cub3D - Raycaster Test");
    if (game.win == NULL)
    {
        printf("Could not initialize the mlx window.");
        return (0);
    }
    game.img = mlx_new_image(game.mlx, 800, 600);
    if (game.img == NULL)
    {
        printf("Could not initialize the mlx image.");
        return (0);
    }
    game.addr = mlx_get_data_addr(game.img, &game.bpp, &game.line_len, &game.endian);
    if (game.addr == NULL)
    {
        printf("Could not initialize the mlx addr.");
        return (0);
    }
    if (mlx_loop_hook(game.mlx, render_frame, &game) == 0)
    {
        printf("mlx_loop_hook is broke.");
        return (0);
    }
    mlx_hook(game.win, 2, 1L<<0, key_hook, &game);
    if (!game.win)
        return (1);
    mlx_loop(game.mlx);
    return (0);
}

int main(int argc, char **argv)
{
    if (argc == 2)
        return (run_parser_mode(argv[1]));
    if (argc == 1)
        return (run_raycaster_demo());
    printf("Usage: %s [map.cub]\n", argv[0]);
    return (1);
}