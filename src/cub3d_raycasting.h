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
    double  dir_x;      // ray yönü
    double  dir_y;
    int     map_x;      // şu an bakılan hücre
    int     map_y;
    double  perp_dist;  // duvara dik mesafe (fish-eye düzeltilmiş)
    int     side;       // 0 = dikey çizgiye çarptı, 1 = yatay çizgiye
}   t_ray;

void    put_pixel(t_game *game, int x, int y, int color);
void    draw_walls(t_game *game, int wall_color);
int     render_frame(t_game *game);

#endif