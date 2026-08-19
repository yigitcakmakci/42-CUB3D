/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 22:54:14 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/08/19 20:31:45 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

static void	update_movement(t_game *game, double speed)
{
	if (game->player.key_control.key_w)
		move_player(game, game->player.dir_x * speed, game->player.dir_y
			* speed);
	if (game->player.key_control.key_s)
		move_player(game, -game->player.dir_x * speed, -game->player.dir_y
			* speed);
	if (game->player.key_control.key_a)
		move_player(game, game->player.dir_y * speed, -game->player.dir_x
			* speed);
	if (game->player.key_control.key_d)
		move_player(game, -game->player.dir_y * speed, game->player.dir_x
			* speed);
}

static void	update_rotation(t_game *game)
{
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

void	update_player(t_game *game)
{
	double	speed;

	speed = 0.05;
	update_movement(game, speed);
	update_rotation(game);
}
