#include "cub3d.h"
#include "cub3d_parser.h"
#include "cub3d_raycasting.h"
#include <stdio.h>
#include <math.h>

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_UP 0xFF52
#define KEY_LEFT 0xFF51
#define KEY_RIGHT 0xFF53
#define KEY_DOWN 65364
#define KEY_ESC 65307

/*static void print_map(t_data *data)
{
    int i;

    printf("Map (%d x %d):\n", data->map_width, data->map_height);
    i = 0;
    while (i < data->map_height)
    {
        printf("%s\n", data->map[i]);
        i++;
    }
}*/

/*static void print_data(t_data *data)
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
}*/

void init_player_from_data(t_game *game)
{
    game->player.pos_x = game->data.player_x + 0.5;
    game->player.pos_y = game->data.player_y + 0.5;

    if (game->data.player_dir == 'N')
        game->player.angle = 3 * M_PI / 2;
    else if (game->data.player_dir == 'S')
        game->player.angle = M_PI / 2;
    else if (game->data.player_dir == 'E')
        game->player.angle = 0;
    else if (game->data.player_dir == 'W')
        game->player.angle = M_PI;
    
    game->player.dir_x = cos(game->player.angle);
    game->player.dir_y = sin(game->player.angle);
}

static int close_game(t_game *game)
{
    free_game(game);
    exit(0);
}

static int is_wall(t_game *game, double x, double y)
{
    int map_x;
    int map_y;

    map_x = (int)x;
    map_y = (int)y;
    if (map_x < 0 || map_y < 0
        || map_y >= game->data.map_height
        || map_x >= game->data.map_width)
        return (1);
    return (game->data.map[map_y][map_x] == '1');
}

static void move_player(t_game *game, double move_x, double move_y)
{
    double new_x;
    double new_y;
    double margin;

    margin = 0.15;

    new_x = game->player.pos_x + move_x;
    new_y = game->player.pos_y + move_y;

    if (!is_wall(game, new_x + margin, game->player.pos_y)
        && !is_wall(game, new_x - margin, game->player.pos_y)
        && !is_wall(game, new_x, game->player.pos_y + margin)
        && !is_wall(game, new_x, game->player.pos_y - margin))
        game->player.pos_x = new_x;

    if (!is_wall(game, game->player.pos_x + margin, new_y)
        && !is_wall(game, game->player.pos_x - margin, new_y)
        && !is_wall(game, game->player.pos_x, new_y + margin)
        && !is_wall(game, game->player.pos_x, new_y - margin))
        game->player.pos_y = new_y;
}

int key_hook(int keycode, t_game *game)
{
    double speed = 0.1;
    if (keycode == KEY_W)
    {
        move_player(game, game->player.dir_x * speed, game->player.dir_y * speed);
    }
    if (keycode == KEY_A)
    {
        move_player(game, -game->player.dir_x * speed, game->player.dir_y * speed);
    }
    if (keycode == KEY_S)
    {
        move_player(game, -game->player.dir_x * speed, -game->player.dir_y * speed);
    }
    if (keycode == KEY_D)
    {
        move_player(game, game->player.dir_x * speed, -game->player.dir_y * speed);
    }
    if (keycode == KEY_RIGHT)
    {
        game->player.angle += 0.05;
        game->player.dir_x = cos(game->player.angle);
        game->player.dir_y = sin(game->player.angle);
    }
    if (keycode == KEY_LEFT)
    {
        game->player.angle -= 0.05;
        game->player.dir_x = cos(game->player.angle);
        game->player.dir_y = sin(game->player.angle);
    }
    if (keycode == KEY_ESC)
    {
        close_game(game);
    }

    
    return (0);
}

static int run_raycaster_demo(t_game *game)
{
    game->window.fov = 60;
    game->window.height = 1080;
    game->window.width = 1920;
    game->conf.mlx = mlx_init();

    if (game->conf.mlx == NULL)
    {
        printf("MLX could not be started");
        return (0);
    }
    
    if (!game->conf.mlx)
        return (1);
    game->conf.win = mlx_new_window(game->conf.mlx, game->window.width, game->window.height, "cub3D - Raycaster Test");
    if (game->conf.win == NULL)
    {
        printf("Could not initialize the mlx window.");
        return (0);
    }
    game->conf.img = mlx_new_image(game->conf.mlx, game->window.width, game->window.height);
    if (game->conf.img == NULL)
    {
        printf("Could not initialize the mlx image.");
        return (0);
    }
    game->conf.addr = mlx_get_data_addr(game->conf.img, &game->conf.bpp, &game->conf.line_len, &game->conf.endian);
    if (game->conf.addr == NULL)
    {
        printf("Could not initialize the mlx addr.");
        return (0);
    }
    if (mlx_loop_hook(game->conf.mlx, render_frame, game) == 0)
    {
        printf("mlx_loop_hook is broke.");
        return (0);
    }
    if (mlx_hook(game->conf.win, 2, 1L<<0, key_hook, game) == 0)
    {
        printf("mlx_hook is broke.");
        return (0);
    }
    if (mlx_hook(game->conf.win, 17, 0, close_game, game) == 0)
    {
        printf("Program is not close true\n");
        return (0);
    }   // 17 = DestroyNotify
    if (!game->conf.win)
        return (1);
    mlx_loop(game->conf.mlx);
    return (0);
}

int main(int argc, char **argv)
{
    t_game game;
    if (argc != 2)
    {
        printf("WRONG ARG COUNT\n");
        return(0);
    }
    
    ft_memset(&game, 0, sizeof(t_game));
    if (parse_file(argv[1], &game.data))
    {
        printf("Error\n");
        return(1);
    }
    init_player_from_data(&game);
    run_raycaster_demo(&game);
    free_game(&game);
    return(0);
}