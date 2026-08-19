/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 21:22:08 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/08/19 20:30:26 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	init_step_x(t_game *game, t_ray *ray, double *side_dist, int *step)
{
	double	delta_x;

	delta_x = fabs(1.0 / ray->dir_x);
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
}

static void	init_step_y(t_game *game, t_ray *ray, double *side_dist, int *step)
{
	double	delta_y;

	delta_y = fabs(1.0 / ray->dir_y);
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

void	init_dda(t_game *game, t_ray *ray, double *side_dist, int *step)
{
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	init_step_x(game, ray, side_dist, step);
	init_step_y(game, ray, side_dist, step);
}
