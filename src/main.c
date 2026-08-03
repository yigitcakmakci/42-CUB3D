#include "cub3d.h"
#include "cub3d_parser.h"
#include <stdio.h>

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

static int run_raycaster_demo(void)
{
    t_game game;

    game.pos_x = 5.5;
    game.pos_y = 5.5;
    game.dir_x = 1.0;
    game.dir_y = 0.0;

    init_dummy_map(&game);
    game.mlx = mlx_init();
    if (!game.mlx)
        return (1);
    game.win = mlx_new_window(game.mlx, 800, 600, "cub3D - Raycaster Test");
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