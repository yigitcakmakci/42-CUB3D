#ifndef CUB3D_RAYCASTING_H
#define CUB3D_RAYCASTING_H

#include "cub3d.h"

typedef struct s_pos
{
    double x;
    double y;
}   t_pos;

typedef struct s_ray
{
    t_pos pos;
}   t_ray;

void    put_pixel(t_game *game, int x, int y, int color);
void    draw_background(t_game *game, int ceiling_color, int floor_color);
void    draw_walls(t_game *game, int wall_color);
int     render_frame(t_game *game);

#endif