/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 20:55:50 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_raycasting.h"
#include "cub3d.h"
#include <unistd.h>
#include <math.h>
#include "cub3d_render.h"

void put_pixel(t_game *game, int x, int y, int color)
{
	if (x < 0 || x >= game->window.width || y < 0 || y >= game->window.height)
		return;
	char *dst = game->conf.addr + (y * game->conf.line_len + x * (game->conf.bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_rect(t_game *game, int x, int y, int w, int h, int color)
{
	int i;
	int j;

	i = 0;
	while (i < w)
	{
		j = 0;
		while (j < h)
		{
			put_pixel(game, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static int rgb_to_hex(int *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static void draw_background(t_game *game)
{
	for (int i = 0; i < game->window.width; i++)
	{
		for (int j = 0; j < (game->window.height / 2); j++)
		{
			put_pixel(game, i, j, rgb_to_hex(game->data.ceiling));
		}
	}
	for (int i = 0; i < game->window.width; i++)
	{
		for (int j = (game->window.height / 2); j < game->window.height; j++)
		{
			put_pixel(game, i, j, rgb_to_hex(game->data.floor));
		}
	}
}

int render_frame(t_game *game)
{
	update_player(game);
	draw_background(game);
	draw_walls(game);
	draw_map(game);
	mlx_put_image_to_window(game->conf.mlx, game->conf.win, game->conf.img, 0, 0);
	return (1);
}
