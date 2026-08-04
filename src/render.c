#include "cub3d_raycasting.h"
#include "cub3d.h"
#include <unistd.h>

void    put_pixel(t_game *game, int x, int y, int color)
{
    char *dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int *)dst = color;
}

static void draw_rect(t_game *game, int x, int y, int w, int h, int color)
{
    int i;
    int j;

    i = 0;
    while (i < w)
    {
        j = 0;
        while (j < h)
        {
            put_pixel(game, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void    draw_background(t_game *game, int ceiling_color, int floor_color)
{
    for (size_t i = 0; i < 800; i++)
    {
        for (size_t j = 0; j < 300; j++)
        {
            put_pixel(game, i, j, floor_color);
        }
    }
    for (size_t i = 0; i < 800; i++)
    {
        for (size_t j = 300; j < 600; j++)
        {
            put_pixel(game, i, j, ceiling_color);
        }
    }

}

void    draw_wall(t_game *game, int wall_color, int distance)
{
    int height = 600 - (distance * 50);
    int width = 800 - (distance * 50);
    int xStart = 600 - height;
    int yStart = 800 - width;
    draw_rect(game, xStart, yStart, width, height, wall_color);
}

void    draw_walls(t_game *game, int wall_color)
{
    t_ray ray;

    ray.pos.x = game->pos_x;
    ray.pos.y = game->pos_y;
    int i = 1;
    while (game->map[(int)ray.pos.x][(int)ray.pos.y] != 1)
    {
        ray.pos.x = game->pos_x + (game->dir_x * i);
        ray.pos.y = game->pos_y + (game->dir_y * i);
        i++;
    }
    draw_wall(game, wall_color, i);
}



void    draw_map(t_game *game)
{
    int map_size;
    int tile;
    int start_x;
    int start_y;
    int frame;
    int mx;
    int my;
    int cell_x;
    int cell_y;
    int px;
    int py;
    int i;
    int rx;
    int ry;

    map_size = 10;
    tile = 14;
    start_x = 800 - (map_size * tile) - 10;
    start_y = 10;
    frame = map_size * tile;

    draw_rect(game, start_x - 2, start_y - 2, frame + 4, frame + 4, 0x00FFFFFF);
    draw_rect(game, start_x, start_y, frame, frame, 0x00222222);

    my = 0;
    while (my < map_size)
    {
        mx = 0;
        while (mx < map_size)
        {
            cell_x = start_x + (mx * tile);
            cell_y = start_y + (my * tile);
            if (game->map[my][mx] == 1)
                draw_rect(game, cell_x, cell_y, tile - 1, tile - 1, 0x00BBBBBB);
            else
                draw_rect(game, cell_x, cell_y, tile - 1, tile - 1, 0x00333333);
            mx++;
        }
        my++;
    }

    px = start_x + (int)(game->pos_x * tile);
    py = start_y + (int)(game->pos_y * tile);
    draw_rect(game, px - 2, py - 2, 5, 5, 0x0000FF00);

    i = 1;
    while (i < 12)
    {
        rx = px + (int)(game->dir_x * i);
        ry = py + (int)(game->dir_y * i);
        put_pixel(game, rx, ry, 0x00FF0000);
        i++;
    }
}

int render_frame(t_game *game)
{
    draw_background(game, 0x00FF0000, 0x0000FF00);
    draw_walls(game, 0x000000FF);
    draw_map(game);
    mlx_put_image_to_window(game->mlx,game->win,game->img, 0, 0);
    return(1);
}