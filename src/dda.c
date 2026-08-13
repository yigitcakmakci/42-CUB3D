/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 21:19:10 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/08/13 21:23:22 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_raycasting.h"
#include "cub3d_render.h"
#include <math.h>

static int	is_wall_hit(t_game *game, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= game->data.map_width || ray->map_y < 0
		|| ray->map_y >= game->data.map_height)
		return (1);
	if (game->data.map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

static void	update_step(t_ray *ray, double *side_dist, double *delta, int *step)
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
		update_step(ray, side_dist, delta, step);
		if (is_wall_hit(game, ray))
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
