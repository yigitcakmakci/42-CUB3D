/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 22:54:22 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/08/13 22:54:24 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	load_single_texture(t_game *game, int i, char *path)
{
	game->texture[i].img = mlx_xpm_file_to_image(game->conf.mlx,
			path, &game->texture[i].width, &game->texture[i].height);
	if (!game->texture[i].img)
	{
		printf("TEXTURE IMG NOT CREATED\n");
		return (0);
	}
	game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,
			&game->texture[i].bpp, &game->texture[i].line_len,
			&game->texture[i].endian);
	if (!game->texture[i].addr)
	{
		printf("TEXTURE IMG NOT CREATED\n");
		return (0);
	}
	return (1);
}

int	init_texture(t_game *game)
{
	char	*xpm_files[4];
	int		i;

	xpm_files[0] = game->data.no;
	xpm_files[1] = game->data.so;
	xpm_files[2] = game->data.we;
	xpm_files[3] = game->data.ea;
	i = 0;
	while (i < 4)
	{
		if (!load_single_texture(game, i, xpm_files[i]))
			return (0);
		i++;
	}
	return (1);
}
