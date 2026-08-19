/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 20:38:01 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/08/19 20:31:23 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_cells(t_game *game, int start_x, int start_y, int tile)
{
	t_rect	rect;
	int		mx;
	int		my;

	rect.w = tile - 1;
	rect.h = tile - 1;
	my = 0;
	while (my < game->data.map_height)
	{
		mx = 0;
		while (mx < game->data.map_width)
		{
			rect.x = start_x + (mx * tile);
			rect.y = start_y + (my * tile);
			if (game->data.map[my][mx] == '1')
				rect.color = 0x00BBBBBB;
			else
				rect.color = 0x00333333;
			draw_rect(game, rect);
			mx++;
		}
		my++;
	}
}

static void	draw_map_bg(t_game *game, int sx, int sy, int tile)
{
	t_rect	r;

	r.w = (game->data.map_width * tile) + 4;
	r.h = (game->data.map_height * tile) + 4;
	r.x = sx - 2;
	r.y = sy - 2;
	r.color = 0x00FFFFFF;
	draw_rect(game, r);
	r.w -= 4;
	r.h -= 4;
	r.x = sx;
	r.y = sy;
	r.color = 0x00222222;
	draw_rect(game, r);
}

void	draw_map(t_game *game)
{
	t_rect	r;
	int		tile;
	int		sx;
	int		sy;

	tile = 14;
	sx = game->window.width - (game->data.map_width * tile) - 10;
	sy = 10;
	draw_map_bg(game, sx, sy, tile);
	draw_map_cells(game, sx, sy, tile);
	r.w = 5;
	r.h = 5;
	r.x = sx + (int)(game->player.pos_x * tile) - 2;
	r.y = sy + (int)(game->player.pos_y * tile) - 2;
	r.color = 0x0000FF00;
	draw_rect(game, r);
}
