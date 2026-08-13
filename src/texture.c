/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 20:54:18 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include "cub3d_raycasting.h"
#include <math.h>

unsigned int get_tex_color(t_texture *tex, int tex_x, int tex_y)
{
	char *src;

	src = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)src);
}

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

int pick_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (2);
		return (3);
	}
	if (ray->dir_y > 0)
		return (0);
	return (1);
}

void print_texture(t_game *game, t_texture *choosed_texture, int wall_height, int top, int bottom, int x, t_ray *ray)
{
	double step = (double)choosed_texture->height / wall_height;
	double tex_pos = (top - (game->window.height - wall_height) / 2.0) * step;
	double wall_x;
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	int tex_x = (int)(wall_x * choosed_texture->width);

	int y = top;
	while (y < bottom)
	{
		int tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= choosed_texture->height)
			tex_y = choosed_texture->height - 1;
		tex_pos += step;
		put_pixel(game, x, y, get_tex_color(choosed_texture, tex_x, tex_y));
		y++;
	}
}

void draw_column(t_game *game, int x, t_ray *ray)
{
	int wall_height;
	int top;
	int bottom;

	if (ray->perp_dist < 0.01)
		ray->perp_dist = 0.01;
	wall_height = (int)(game->window.height / ray->perp_dist);
	top = (game->window.height - wall_height) / 2;
	if (top < 0)
		top = 0;
	bottom = (game->window.height + wall_height) / 2;
	if (bottom > game->window.height)
		bottom = game->window.height;
	int texture_dir = pick_texture(ray);
	t_texture chosed_texture = game->texture[texture_dir];
	print_texture(game, &chosed_texture, wall_height, top, bottom, x, ray);
}
