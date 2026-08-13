/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 20:38:01 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/08/13 21:04:03 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_raycasting.h"
#include "cub3d_render.h"
#include <math.h>

void	draw_map_cells(t_game *game, int start_x, int start_y, int tile)
{
	int	mx;
	int	my;
	int	c_x;
	int	c_y;

	my = 0;
	while (my < game->data.map_height)
	{
		mx = 0;
		while (mx < game->data.map_width)
		{
			c_x = start_x + (mx * tile);
			c_y = start_y + (my * tile);
			if (game->data.map[my][mx] == '1')
				draw_rect(game, c_x, c_y, tile - 1, tile - 1, 0x00BBBBBB);
			else
				draw_rect(game, c_x, c_y, tile - 1, tile - 1, 0x00333333);
			mx++;
		}
		my++;
	}
}

void	draw_map(t_game *game)
{
	int	tile;
	int	start_x;
	int	start_y;
	int	px;
	int	py;

	tile = 14;
	start_x = game->window.width - (game->data.map_width * tile) - 10;
	start_y = 10;
	draw_rect(game, start_x - 2, start_y - 2, (game->data.map_width * tile) + 4,
		(game->data.map_height * tile) + 4, 0x00FFFFFF);
	draw_rect(game, start_x, start_y, (game->data.map_width * tile),
		(game->data.map_height * tile), 0x00222222);
	draw_map_cells(game, start_x, start_y, tile);
	px = start_x + (int)(game->player.pos_x * tile);
	py = start_y + (int)(game->player.pos_y * tile);
	draw_rect(game, px - 2, py - 2, 5, 5, 0x0000FF00);
}

void	update_player(t_game *game)
{
	double	speed;

	speed = 0.05;
	if (game->player.key_control.key_W)
		move_player(game, game->player.dir_x * speed, game->player.dir_y
			* speed);
	if (game->player.key_control.key_S)
		move_player(game, -game->player.dir_x * speed, -game->player.dir_y
			* speed);
	if (game->player.key_control.key_A)
		move_player(game, game->player.dir_y * speed, -game->player.dir_x
			* speed);
	if (game->player.key_control.key_D)
		move_player(game, -game->player.dir_y * speed, game->player.dir_x
			* speed);
	if (game->player.key_control.key_left_arrow)
	{
		game->player.angle -= 0.03;
		game->player.dir_x = cos(game->player.angle);
		game->player.dir_y = sin(game->player.angle);
	}
	if (game->player.key_control.key_right_arrow)
	{
		game->player.angle += 0.03;
		game->player.dir_x = cos(game->player.angle);
		game->player.dir_y = sin(game->player.angle);
	}
}
