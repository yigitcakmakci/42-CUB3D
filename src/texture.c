/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alozpola <alozpola@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */
/*   Updated: 2025/06/19 22:55:26 by alozpola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int init_texture(t_game *game)
{
	char *xpm_files[4];
	xpm_files[0] = game->data.no;
	xpm_files[1] = game->data.so;
	xpm_files[2] = game->data.we;
	xpm_files[3] = game->data.ea;
	for (size_t i = 0; i < 4; i++)
	{
		printf("IMHERE\n");
		if((game->texture[i].img = mlx_xpm_file_to_image(game->conf.mlx ,xpm_files[i], &game->texture[i].width, &game->texture[i].height)) == 0)
		{
			printf("TEXTURE IMG NOT CREATED\n");
			return (0);
		}
		if((game->texture[i].addr = mlx_get_data_addr(game->texture[i].img, &game->texture[i].bpp, &game->texture[i].line_len, &game->texture[i].endian)) == 0)
		{
			printf("TEXTURE IMG NOT CREATED\n");
			return (0);
		}
	}
	return (1);
}
