/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 21:31:08 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/08/13 21:41:37 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 0xFF51
#define KEY_RIGHT 0xFF53
#define KEY_ESC 65307

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.key_control.key_W = 0;
	if (keycode == KEY_A)
		game->player.key_control.key_A = 0;
	if (keycode == KEY_S)
		game->player.key_control.key_S = 0;
	if (keycode == KEY_D)
		game->player.key_control.key_D = 0;
	if (keycode == KEY_LEFT)
		game->player.key_control.key_left_arrow = 0;
	if (keycode == KEY_RIGHT)
		game->player.key_control.key_right_arrow = 0;
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.key_control.key_W = 1;
	if (keycode == KEY_A)
		game->player.key_control.key_A = 1;
	if (keycode == KEY_S)
		game->player.key_control.key_S = 1;
	if (keycode == KEY_D)
		game->player.key_control.key_D = 1;
	if (keycode == KEY_RIGHT)
		game->player.key_control.key_right_arrow = 1;
	if (keycode == KEY_LEFT)
		game->player.key_control.key_left_arrow = 1;
	if (keycode == KEY_ESC)
		close_game(game);
	return (0);
}
