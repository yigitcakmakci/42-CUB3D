#include "cub3d.h"

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

    // Matrisi game->map içine kopyalama işlemi
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
            game->map[y][x] = dummy[y][x];
    }
}

int main(void)
{
    t_game game;

    // Oyuncu başlangıç değerleri (Örn: haritanın ortası)
    game.pos_x = 5.5; 
    game.pos_y = 5.5;
    
    // Bakış yönü (Örn: Doğuya bakıyor)
    game.dir_x = 1.0;
    game.dir_y = 0.0;

    init_dummy_map(&game);

    // MLX Başlatma
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, 800, 600, "cub3D - Raycaster Test");

    // X butonuna basınca kapanması için temel hook
    // mlx_hook(game.win, 17, 0, close_window, &game);

    // Sonsuz döngü
    mlx_loop(game.mlx);

    return (0);
}