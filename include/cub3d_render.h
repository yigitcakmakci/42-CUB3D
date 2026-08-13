#ifndef CUB3D_RENDER_H
#define CUB3D_RENDER_H

#include "cub3d.h"
#include "cub3d_raycasting.h"

void	run_dda(t_game *game, t_ray *ray);
void	init_dda(t_game *game, t_ray *ray,double *side_dist, int *step);
void	draw_walls(t_game *game);
int		pick_texture(t_ray *ray);
void	print_texture(t_game *game, t_texture *choosed_texture, int wall_height, int top, int bottom, int x, t_ray *ray);
void	draw_map_cells(t_game *game, int start_x, int start_y, int tile);
void	draw_map(t_game *game);
void	update_player(t_game *game);
void	draw_column(t_game *game, int x, t_ray *ray);
void	draw_rect(t_game *game, t_rect rect);
void	update_player(t_game *game);

#endif