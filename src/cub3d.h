#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"
#include "cub3d_parser.h"

typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  angle;
} t_player;

typedef struct s_window
{
    int height;
    int width;
    int fov;
} t_window;

typedef struct s_configuration
{
    void        *mlx;
    void        *win;
    void        *img;
    char        *addr;
    int         bpp;
    int         line_len;
    int         endian;
} t_configuration;

typedef struct s_game
{
    t_data          data;
    t_window        window;
    t_configuration conf;
    t_player        player;
}   t_game;

int free_game(t_game *game);

#endif