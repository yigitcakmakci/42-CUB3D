/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 20:40:06 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parser.h"
#include "cub3d_raycasting.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free(data->no);
	free(data->so);
	free(data->we);
	free(data->ea);
	free_map(data->map);
	ft_memset(data, 0, sizeof(t_data));
}

void	free_conf(t_configuration *conf)
{
	if (!conf || !conf->mlx)
		return ;
	if (conf->img)
		mlx_destroy_image(conf->mlx, conf->img);
	if (conf->win)
		mlx_destroy_window(conf->mlx, conf->win);
	mlx_destroy_display(conf->mlx);
	free(conf->mlx);
	conf->img = NULL;
	conf->win = NULL;
	conf->addr = NULL;
	conf->mlx = NULL;
}

void	free_texture(t_texture *texture, void *mlx)
{
	int	i;

	if (!texture)
		return ;
	i = 0;
	while (i < 4)
	{
		if (texture[i].img)
		{
			if (texture[i].img)
				mlx_destroy_image(mlx, texture[i].img);
			texture[i].img = NULL;
			texture[i].addr = NULL;
		}
		else
			return ;
		i++;
	}
	return ;
}

int	free_game(t_game *game)
{
	if (!game)
		return (0);
	free_data(&game->data);
	free_texture(game->texture, game->conf.mlx);
	free_conf(&game->conf);
	return (0);
}
