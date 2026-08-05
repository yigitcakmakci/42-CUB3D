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

static  int rgb_to_hex(int *rgb)
{
    return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static void    draw_background(t_game *game)
{
    for (int i = 0; i < game->window.width; i++)
    {
        for (int j = 0; j < (game->window.height/2); j++)
        {
            put_pixel(game, i, j, rgb_to_hex(game->data.ceiling));
        }
    }
    for (int i = 0; i < game->window.width; i++)
    {
        for (int j = (game->window.height / 2); j < game->window.height; j++)
        {
            put_pixel(game, i, j, rgb_to_hex(game->data.floor));
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

// KURULUM: ray'in yönüne göre adım yönünü ve ilk sınır mesafelerini hesapla
static void init_dda(t_game *game, t_ray *ray,
        double *side_dist, int *step)
{
    double  delta_x;
    double  delta_y;

    ray->map_x = (int)game->player.pos_x;          // hangi hücredeyim?
    ray->map_y = (int)game->player.pos_y;
    delta_x = fabs(1.0 / ray->dir_x);              // x'te 1 hücre = bu kadar ışın yolu
    delta_y = fabs(1.0 / ray->dir_y);
    if (ray->dir_x < 0)                            // sola gidiyorsak
    {
        step[0] = -1;
        side_dist[0] = (game->player.pos_x - ray->map_x) * delta_x;
    }
    else                                           // sağa gidiyorsak
    {
        step[0] = 1;
        side_dist[0] = (ray->map_x + 1.0 - game->player.pos_x) * delta_x;
    }
    if (ray->dir_y < 0)                            // yukarı gidiyorsak
    {
        step[1] = -1;
        side_dist[1] = (game->player.pos_y - ray->map_y) * delta_y;
    }
    else                                           // aşağı gidiyorsak
    {
        step[1] = 1;
        side_dist[1] = (ray->map_y + 1.0 - game->player.pos_y) * delta_y;
    }
}

// DÖNGÜ: duvar bulana kadar hücreden hücreye zıpla
static void run_dda(t_game *game, t_ray *ray)
{
    double  side_dist[2];
    double  delta[2];
    int     step[2];

    init_dda(game, ray, side_dist, step);
    delta[0] = fabs(1.0 / ray->dir_x);
    delta[1] = fabs(1.0 / ray->dir_y);
    while (1)
    {
        if (side_dist[0] < side_dist[1])           // dikey çizgi daha yakın
        {
            side_dist[0] += delta[0];
            ray->map_x += step[0];
            ray->side = 0;
        }
        else                                       // yatay çizgi daha yakın
        {
            side_dist[1] += delta[1];
            ray->map_y += step[1];
            ray->side = 1;
        }
        if (ray->map_x < 0 || ray->map_x >= game->data.map_width
            || ray->map_y < 0 || ray->map_y >= game->data.map_height)
            break ;                                // harita dışı: güvenlik
        if (game->data.map[ray->map_y][ray->map_x] == '1')
            break ;                                // duvar bulundu
    }
    // side_dist zaten bir delta fazla ilerlemiş durumda, geri al:
    if (ray->side == 0)
        ray->perp_dist = side_dist[0] - delta[0];
    else
        ray->perp_dist = side_dist[1] - delta[1];
}

// Bir ekran sütununa duvar dilimini çiz
static void draw_column(t_game *game, int x, t_ray *ray, int color)
{
    int wall_height;
    int top;
    int bottom;
    int y;

    if (ray->perp_dist < 0.01)
        ray->perp_dist = 0.01;
    wall_height = (int)(game->window.height / ray->perp_dist);
    top = (game->window.height - wall_height) / 2;
    if (top < 0)
        top = 0;
    bottom = (game->window.height + wall_height) / 2;
    if (bottom > game->window.height)
        bottom = game->window.height;
    if (ray->side == 1)                            // yatay duvarları koyulaştır (derinlik hissi)
        color = (color >> 1) & 0x7F7F7F;
    y = top;
        y = top;
    while (y < bottom)
    {
        put_pixel(game, x, y, color);
        y++;
    }
}

void    draw_walls(t_game *game, int wall_color)
{
    t_ray   ray;
    int     x;
    double  camera_x;
    double  half_fov;

    half_fov = tan((game->window.fov / 2.0) * (M_PI / 180.0));
    x = 0;
    while (x < game->window.width)
    {
        // ekran sütununu -1..+1 aralığına çevir
        camera_x = 2.0 * x / (double)game->window.width - 1.0;
        ray.dir_x = game->player.dir_x - game->player.dir_y * camera_x * half_fov;
        ray.dir_y = game->player.dir_y + game->player.dir_x * camera_x * half_fov;
        run_dda(game, &ray);
        draw_column(game, x, &ray, wall_color);
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
    draw_background(game);
    draw_walls(game, 0x000000FF);
    draw_map(game);
    mlx_put_image_to_window(game->conf.mlx,game->conf.win,game->conf.img, 0, 0);
    return(1);
}