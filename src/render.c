/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alozpola <alozpola@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */
/*   Updated: 2025/06/19 22:55:26 by alozpola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_raycasting.h"
#include "cub3d.h"
#include <unistd.h>
#include <math.h>

void put_pixel(t_game *game, int x, int y, int color)
{
	if (x < 0 || x >= game->window.width || y < 0 || y >= game->window.height)
		return;
	char *dst = game->conf.addr + (y * game->conf.line_len + x * (game->conf.bpp / 8));
	*(unsigned int *)dst = color;
}

static void draw_rect(t_game *game, int x, int y, int w, int h, int color)
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

void draw_wall(t_game *game, int wall_color, int distance)
{
	int height = game->window.height - (distance * 50);
	int width = game->window.width - (distance * 50);
	int xStart = game->window.height - height;
	int yStart = game->window.width - width;
	draw_rect(game, xStart, yStart, width, height, wall_color);
}

static void init_dda(t_game *game, t_ray *ray,
					 double *side_dist, int *step)
{
	double delta_x;
	double delta_y;

	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	delta_x = fabs(1.0 / ray->dir_x);
	delta_y = fabs(1.0 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		step[0] = -1;
		side_dist[0] = (game->player.pos_x - ray->map_x) * delta_x;
	}
	else
	{
		step[0] = 1;
		side_dist[0] = (ray->map_x + 1.0 - game->player.pos_x) * delta_x;
	}
	if (ray->dir_y < 0)
	{
		step[1] = -1;
		side_dist[1] = (game->player.pos_y - ray->map_y) * delta_y;
	}
	else
	{
		step[1] = 1;
		side_dist[1] = (ray->map_y + 1.0 - game->player.pos_y) * delta_y;
	}
}

static void run_dda(t_game *game, t_ray *ray)
{
	double side_dist[2];
	double delta[2];
	int step[2];

	init_dda(game, ray, side_dist, step);
	delta[0] = fabs(1.0 / ray->dir_x);
	delta[1] = fabs(1.0 / ray->dir_y);
	while (1)
	{
		if (side_dist[0] < side_dist[1])
		{
			side_dist[0] += delta[0];
			ray->map_x += step[0];
			ray->side = 0;
		}
		else
		{
			side_dist[1] += delta[1];
			ray->map_y += step[1];
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= game->data.map_width || ray->map_y < 0 || ray->map_y >= game->data.map_height)
			break; // harita dışı: güvenlik
		if (game->data.map[ray->map_y][ray->map_x] == '1')
			break; // duvar bulundu
	}
	// side_dist zaten bir delta fazla ilerlemiş durumda, geri al:
	if (ray->side == 0)
		ray->perp_dist = side_dist[0] - delta[0];
	else
		ray->perp_dist = side_dist[1] - delta[1];
}

unsigned int get_tex_color(t_texture *tex, int tex_x, int tex_y)
{
	char *src;

	src = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)src);
}

static int pick_texture(t_ray *ray)
{
	if (ray->side == 0) // x ekseninde çarptı (doğu/batı yüzü)
	{
		if (ray->dir_x > 0)
			return (2); // WE
		return (3);     // EA
	}
	if (ray->dir_y > 0) // y ekseninde çarptı (kuzey/güney yüzü)
		return (0);     // NO
	return (1);         // SO
}

static void print_texture(t_game *game, t_texture *choosed_texture, int wall_height, int top, int bottom, int x, t_ray *ray)
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

// Bir ekran sütununa duvar dilimini çiz
static void draw_column(t_game *game, int x, t_ray *ray)
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

void draw_walls(t_game *game)
{
	t_ray ray;
	int x;
	double camera_x;
	double half_fov;

	half_fov = tan((game->window.fov / 2.0) * (M_PI / 180.0));
	x = 0;
	while (x < game->window.width)
	{
		// ekran sütununu -1..+1 aralığına çevir
		camera_x = 2.0 * x / (double)game->window.width - 1.0;
		ray.dir_x = game->player.dir_x - game->player.dir_y * camera_x * half_fov;
		ray.dir_y = game->player.dir_y + game->player.dir_x * camera_x * half_fov;
		run_dda(game, &ray);
		draw_column(game, x, &ray);
		x++;
	}
}

void draw_map(t_game *game)
{
	int tile;
	int start_x;
	int start_y;
	int mx;
	int my;
	int cell_x;
	int cell_y;
	int px;
	int py;
	int i;
	int rx;
	int ry;

	int map_h = game->data.map_height;
	int map_w = game->data.map_width;
	tile = 14;
	start_x = game->window.width - (map_w * tile) - 10;
	start_y = 10;
	int frame_w = map_w * tile;
	int frame_h = map_h * tile;

	draw_rect(game, start_x - 2, start_y - 2, frame_w + 4, frame_h + 4, 0x00FFFFFF);
	draw_rect(game, start_x, start_y, frame_w, frame_h, 0x00222222);

	my = 0;
	while (my < map_h)
	{
		mx = 0;
		while (mx < map_w)
		{
			cell_x = start_x + (mx * tile);
			cell_y = start_y + (my * tile);
			if (game->data.map[my][mx] == '1')
				draw_rect(game, cell_x, cell_y, tile - 1, tile - 1, 0x00BBBBBB);
			else
				draw_rect(game, cell_x, cell_y, tile - 1, tile - 1, 0x00333333);
			mx++;
		}
		my++;
	}

	px = start_x + (int)(game->player.pos_x * tile);
	py = start_y + (int)(game->player.pos_y * tile);
	draw_rect(game, px - 2, py - 2, 5, 5, 0x0000FF00);

	i = 1;
	while (i < 12)
	{
		rx = px + (int)(game->player.dir_x * i);
		ry = py + (int)(game->player.dir_y * i);
		put_pixel(game, rx, ry, 0x00FF0000);
		i++;
	}
}

void update_player(t_game *game)
{
	double speed = 0.05;

	if (game->player.key_control.key_W)
		move_player(game, game->player.dir_x * speed, game->player.dir_y * speed);
	if (game->player.key_control.key_S)
		move_player(game, -game->player.dir_x * speed, -game->player.dir_y * speed);
	if (game->player.key_control.key_A)
		move_player(game, game->player.dir_y * speed, -game->player.dir_x * speed);
	if (game->player.key_control.key_D)
		move_player(game, -game->player.dir_y * speed, game->player.dir_x * speed);
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

int render_frame(t_game *game)
{
	update_player(game);
	draw_background(game);
	draw_walls(game);
	draw_map(game);
	mlx_put_image_to_window(game->conf.mlx, game->conf.win, game->conf.img, 0, 0);
	return (1);
}
