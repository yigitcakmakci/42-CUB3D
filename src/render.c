#include "cub3d_raycasting.h"
#include "cub3d.h"
#include <unistd.h>
#include <math.h>

void    put_pixel(t_game *game, int x, int y, int color)
{
    if (x < 0 || x >= game->window.width || y < 0 || y >= game->window.height)
        return;
    char *dst = game->conf.addr + (y * game->conf.line_len + x * (game->conf.bpp / 8));
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
    for (int i = 0; i < game->window.width; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            put_pixel(game, i, j, floor_color);
        }
    }
    for (int i = 0; i < game->window.width; i++)
    {
        for (int j = 300; j < game->window.height; j++)
        {
            put_pixel(game, i, j, ceiling_color);
        }
    }

}

void    draw_wall(t_game *game, int wall_color, int distance)
{
    int height = game->window.height - (distance * 50);
    int width = game->window.width - (distance * 50);
    int xStart = game->window.height - height;
    int yStart = game->window.width - width;
    draw_rect(game, xStart, yStart, width, height, wall_color);
}

void    draw_walls(t_game *game, int wall_color)
{
    int x = 0;
    while (x < game->window.width)
    {
        float half_fov_rad = (game->window.fov / 2.0) * (M_PI / 180.0);

        // Eski sabit değer yerine bu yeni dinamik değişkeni kullan
        float angle = game->player.angle + atan(((float)(x - (game->window.width / 2)) / (float)(game->window.width / 2)) * tan(half_fov_rad));
        float ray_dx = cos(angle);
        float ray_dy = sin(angle);
        float distance = 0;
        float step = 0.01;
        float ray_x = game->player.pos_x;
        float ray_y = game->player.pos_y;
        while (distance < 100)  // Max mesafe
        {
            ray_x += ray_dx * step;
            ray_y += ray_dy * step;
            distance += step;
            
            // Harita sınırları kontrol et
            if ((int)ray_x < 0 || (int)ray_x >= game->data.map_width ||
                (int)ray_y < 0 || (int)ray_y >= game->data.map_height)
                break;
            
            // Duvara çarptı mı?
            if (game->data.map[(int)ray_y][(int)ray_x] == '1')
                break;
        }
        
        float perp_distance = distance * cos(angle - game->player.angle);
        if (perp_distance < 0.1) perp_distance = 0.1; 

        int wall_height = (int)(game->window.height / perp_distance);
        
        // Duvarı çiz (dikey çizgi olarak)
        int top = (game->window.height - wall_height) / 2;
        if (top < 0) top = 0;
        int bottom = (game->window.height + wall_height) / 2;
        if (bottom > game->window.height) bottom = game->window.height;
        
        for (int y = top; y < bottom; y++)
                put_pixel(game, x, y, wall_color);
        x++;
    }
}



void    draw_map(t_game *game)
{
    int tile;
    int start_x;
    int start_y;
    int mx;
    int my;
    int cell_x;
    int cell_y;
    int px;
    int py;
    int i;
    int rx;
    int ry;

    int map_h = game->data.map_height;
    int map_w = game->data.map_width;
    tile = 14;
    start_x = game->window.width - (map_w * tile) - 10;
    start_y = 10;
    int frame_w = map_w * tile;
    int frame_h = map_h * tile;

    draw_rect(game, start_x - 2, start_y - 2, frame_w + 4, frame_h + 4, 0x00FFFFFF);
    draw_rect(game, start_x, start_y, frame_w, frame_h, 0x00222222);

    my = 0;
    while (my < map_h)
    {
        mx = 0;
        while (mx < map_w)
        {
            cell_x = start_x + (mx * tile);
            cell_y = start_y + (my * tile);
            if (game->data.map[my][mx] == '1')
                draw_rect(game, cell_x, cell_y, tile - 1, tile - 1, 0x00BBBBBB);
            else
                draw_rect(game, cell_x, cell_y, tile - 1, tile - 1, 0x00333333);
            mx++;
        }
        my++;
    }

    px = start_x + (int)(game->player.pos_x * tile);
    py = start_y + (int)(game->player.pos_y * tile);
    draw_rect(game, px - 2, py - 2, 5, 5, 0x0000FF00);

    i = 1;
    while (i < 12)
    {
        rx = px + (int)(game->player.dir_x * i);
        ry = py + (int)(game->player.dir_y * i);
        put_pixel(game, rx, ry, 0x00FF0000);
        i++;
    }
}

int render_frame(t_game *game)
{
    draw_background(game, 0x00FF0000, 0x0000FF00);
    draw_walls(game, 0x000000FF);
    draw_map(game);
    mlx_put_image_to_window(game->conf.mlx,game->conf.win,game->conf.img, 0, 0);
    return(1);
}