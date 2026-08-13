/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 21:41:59 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/08/13 21:42:03 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	init_player_from_data(t_game *game)
{
	game->player.pos_x = game->data.player_x + 0.5;
	game->player.pos_y = game->data.player_y + 0.5;
	if (game->data.player_dir == 'N')
		game->player.angle = 3 * M_PI / 2;
	else if (game->data.player_dir == 'S')
		game->player.angle = M_PI / 2;
	else if (game->data.player_dir == 'E')
		game->player.angle = 0;
	else if (game->data.player_dir == 'W')
		game->player.angle = M_PI;
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}

static int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_y >= game->data.map_height
		|| map_x >= game->data.map_width)
		return (1);
	return (game->data.map[map_y][map_x] == '1');
}

void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	double	margin;

	margin = 0.15;
	new_x = game->player.pos_x + move_x;
	new_y = game->player.pos_y + move_y;
	if (!is_wall(game, new_x + margin, game->player.pos_y) && !is_wall(game,
			new_x - margin, game->player.pos_y) && !is_wall(game, new_x,
			game->player.pos_y + margin) && !is_wall(game, new_x,
			game->player.pos_y - margin))
		game->player.pos_x = new_x;
	if (!is_wall(game, game->player.pos_x + margin, new_y) && !is_wall(game,
			game->player.pos_x - margin, new_y) && !is_wall(game,
			game->player.pos_x, new_y + margin) && !is_wall(game,
			game->player.pos_x, new_y - margin))
		game->player.pos_y = new_y;
}
