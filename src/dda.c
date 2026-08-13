/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 20:34:20 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/08/13 21:03:43 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_raycasting.h"
#include "cub3d_render.h"
#include <math.h>

void	init_dda(t_game *game, t_ray *ray, double *side_dist, int *step)
{
	double	delta_x;
	double	delta_y;

	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	delta_x = fabs(1.0 / ray->dir_x);
	delta_y = fabs(1.0 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		step[0] = -1;
		side_dist[0] = (game->player.pos_x - ray->map_x) * delta_x;
	}
	else
	{
		step[0] = 1;
		side_dist[0] = (ray->map_x + 1.0 - game->player.pos_x) * delta_x;
	}
	if (ray->dir_y < 0)
	{
		step[1] = -1;
		side_dist[1] = (game->player.pos_y - ray->map_y) * delta_y;
	}
	else
	{
		step[1] = 1;
		side_dist[1] = (ray->map_y + 1.0 - game->player.pos_y) * delta_y;
	}
}

void	run_dda(t_game *game, t_ray *ray)
{
	double	side_dist[2];
	double	delta[2];
	int		step[2];

	init_dda(game, ray, side_dist, step);
	delta[0] = fabs(1.0 / ray->dir_x);
	delta[1] = fabs(1.0 / ray->dir_y);
	while (1)
	{
		if (side_dist[0] < side_dist[1])
		{
			side_dist[0] += delta[0];
			ray->map_x += step[0];
			ray->side = 0;
		}
		else
		{
			side_dist[1] += delta[1];
			ray->map_y += step[1];
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= game->data.map_width
			|| ray->map_y < 0 || ray->map_y >= game->data.map_height)
			break ;
		if (game->data.map[ray->map_y][ray->map_x] == '1')
			break ;
	}
	if (ray->side == 0)
		ray->perp_dist = side_dist[0] - delta[0];
	else
		ray->perp_dist = side_dist[1] - delta[1];
}

void	draw_walls(t_game *game)
{
	t_ray	ray;
	int		x;
	double	camera_x;
	double	half_fov;

	half_fov = tan((game->window.fov / 2.0) * (M_PI / 180.0));
	x = 0;
	while (x < game->window.width)
	{
		camera_x = 2.0 * x / (double)game->window.width - 1.0;
		ray.dir_x = game->player.dir_x - game->player.dir_y * camera_x
			* half_fov;
		ray.dir_y = game->player.dir_y + game->player.dir_x * camera_x
			* half_fov;
		run_dda(game, &ray);
		draw_column(game, x, &ray);
		x++;
	}
}
