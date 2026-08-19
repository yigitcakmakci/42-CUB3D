/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:40:20 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/19 21:36:01 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	check_player(t_data *data)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				count++;
				data->player_x = x;
				data->player_y = y;
				data->player_dir = data->map[y][x];
				data->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (count != 1);
}

int	chars_checker(t_data *data)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			c = data->map[y][x];
			if (!ft_strchr("01NSEW ", c))
				return (1);
			x++;
		}
		y++;
	}
	return (check_player(data));
}

static int	flood(t_data *data, char **map, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map_width
		|| y >= data->map_height)
		return (1);
	if (map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1')
		return (0);
	if (map[y][x] == 'F')
		return (0);
	map[y][x] = 'F';
	if (flood(data, map, x + 1, y))
		return (1);
	if (flood(data, map, x - 1, y))
		return (1);
	if (flood(data, map, x, y + 1))
		return (1);
	if (flood(data, map, x, y - 1))
		return (1);
	return (0);
}

static int	validate_flood(t_data *data)
{
	char	**copy;
	int		ret;
	int		i;

	copy = malloc(sizeof(char *) * (data->map_height + 1));
	if (!copy)
		return (1);
	i = 0;
	while (i < data->map_height)
	{
		copy[i] = ft_strdup(data->map[i]);
		if (!copy[i])
		{
			copy[i] = NULL;
			free_map(copy);
			return (1);
		}
		i++;
	}
	copy[i] = NULL;
	ret = flood(data, copy, data->player_x, data->player_y);
	free_map(copy);
	return (ret);
}
