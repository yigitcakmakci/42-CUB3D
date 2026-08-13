/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 22:54:28 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/08/13 22:54:31 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_raycasting.h"
#include <math.h>

unsigned int	get_tex_color(t_texture *tex, int tex_x, int tex_y)
{
	char	*src;

	src = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)src);
}

static int	pick_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (2);
		return (3);
	}
	if (ray->dir_y > 0)
		return (0);
	return (1);
}

static int	get_tex_x(t_game *game, t_texture *tex, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return ((int)(wall_x * (double)tex->width));
}

static void	print_texture(t_game *game, t_texture *tex, int x, int *v)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;

	step = (double)tex->height / v[0];
	tex_pos = (v[1] - (game->window.height - v[0]) / 2.0) * step;
	y = v[1];
	while (y < v[2])
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		put_pixel(game, x, y, get_tex_color(tex, v[3], tex_y));
		tex_pos += step;
		y++;
	}
}

void	draw_column(t_game *game, int x, t_ray *ray)
{
	int			v[4];
	t_texture	*tex;

	if (ray->perp_dist < 0.01)
		ray->perp_dist = 0.01;
	v[0] = (int)(game->window.height / ray->perp_dist);
	v[1] = (game->window.height - v[0]) / 2;
	if (v[1] < 0)
		v[1] = 0;
	v[2] = (game->window.height + v[0]) / 2;
	if (v[2] > game->window.height)
		v[2] = game->window.height;
	tex = &game->texture[pick_texture(ray)];
	v[3] = get_tex_x(game, tex, ray);
	print_texture(game, tex, x, v);
}
