/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycasting.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/06 21:34:16 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_RAYCASTING_H
#define CUB3D_RAYCASTING_H

#include "cub3d.h"

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	perp_dist;
	int		side;
}	t_ray;

void	put_pixel(t_game *game, int x, int y, int color);
void	draw_walls(t_game *game);
int		render_frame(t_game *game);
void	move_player(t_game *game, double move_x, double move_y);

#endif
