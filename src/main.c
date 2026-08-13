/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 21:36:51 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/08/13 22:56:55 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parser.h"
#include "cub3d_raycasting.h"
#include "mlx.h"
#include <stdio.h>

static int	init_mlx_window(t_game *game)
{
	game->window.fov = 77;
	game->window.height = 1080;
	game->window.width = 1920;
	game->conf.mlx = mlx_init();
	if (!game->conf.mlx)
	{
		printf("MLX could not be started\n");
		return (0);
	}
	game->conf.win = mlx_new_window(game->conf.mlx, game->window.width,
			game->window.height, "cub3D");
	if (!game->conf.win)
	{
		printf("Could not initialize the mlx window.\n");
		return (0);
	}
	return (1);
}

static int	init_mlx_graphics(t_game *game)
{
	game->conf.img = mlx_new_image(game->conf.mlx, game->window.width,
			game->window.height);
	if (!game->conf.img)
	{
		printf("Could not initialize the mlx image.\n");
		return (0);
	}
	if (init_texture(game) == 0)
	{
		printf("Could not initalize the texture\n");
		return (0);
	}
	game->conf.addr = mlx_get_data_addr(game->conf.img, &game->conf.bpp,
			&game->conf.line_len, &game->conf.endian);
	if (!game->conf.addr)
	{
		printf("Could not initialize the mlx addr.\n");
		return (0);
	}
	return (1);
}

static int	setup_mlx_hooks(t_game *game)
{
	if (mlx_loop_hook(game->conf.mlx, render_frame, game) == 0)
	{
		printf("mlx_loop_hook is broke.\n");
		return (0);
	}
	if (mlx_hook(game->conf.win, 2, 1L << 0, key_press, game) == 0)
	{
		printf("mlx_hook(key_press) is broke.\n");
		return (0);
	}
	if (mlx_hook(game->conf.win, 3, 1L << 1, key_release, game) == 0)
	{
		printf("mlx_hook(key_release) is broke.\n");
		return (0);
	}
	if (mlx_hook(game->conf.win, 17, 0, close_game, game) == 0)
	{
		printf("Program is not close true\n");
		return (0);
	}
	return (1);
}

static int	run_raycaster(t_game *game)
{
	if (!init_mlx_window(game))
		return (0);
	if (!init_mlx_graphics(game))
		return (0);
	if (!setup_mlx_hooks(game))
		return (0);
	mlx_loop(game->conf.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("WRONG ARG COUNT\n");
		return (0);
	}
	ft_memset(&game, 0, sizeof(t_game));
	if (parse_file(argv[1], &game.data))
	{
		printf("Error\n");
		return (1);
	}
	init_player_from_data(&game);
	run_raycaster(&game);
	free_game(&game);
	return (0);
}
