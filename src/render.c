/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 22:39:01 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_raycasting.h"
#include "cub3d_render.h"
#include <math.h>
#include <unistd.h>

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= game->window.width || y < 0 || y >= game->window.height)
		return ;
	dst = game->conf.addr + (y * game->conf.line_len + x * (game->conf.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_game *game, t_rect rect)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.w)
	{
		j = 0;
		while (j < rect.h)
		{
			put_pixel(game, rect.x + i, rect.y + j, rect.color);
			j++;
		}
		i++;
	}
}

static int	rgb_to_hex(int *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static void	draw_background(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->window.width)
	{
		j = 0;
		while (j < (game->window.height / 2))
		{
			put_pixel(game, i, j, rgb_to_hex(game->data.ceiling));
			j++;
		}
		i++;
	}
	i = 0;
	while (i < game->window.width)
	{
		j = (game->window.height / 2);
		while (j < game->window.height)
		{
			put_pixel(game, i, j, rgb_to_hex(game->data.floor));
			j++;
		}
		i++;
	}
}

int	render_frame(t_game *game)
{
	update_player(game);
	draw_background(game);
	draw_walls(game);
	mlx_put_image_to_window(game->conf.mlx, game->conf.win, game->conf.img, 0,
		0);
	return (1);
}
