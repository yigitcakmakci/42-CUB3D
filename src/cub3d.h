#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     map[10][10]; // Geçici statik harita
    double  pos_x;       // Oyuncunun X konumu
    double  pos_y;       // Oyuncunun Y konumu
    double  dir_x;       // Oyuncunun bakış yönü (X vektörü)
    double  dir_y;       // Oyuncunun bakış yönü (Y vektörü)
}   t_game;

#endif