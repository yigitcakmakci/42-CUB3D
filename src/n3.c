/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:35:41 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 23:22:07 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int	parse_config(char *line, t_data *data)
{
	if (!ft_strncmp(line, "NO", 2) && ft_isspace(line[2]))
		return (parse_texture(line, &data->no));
	if (!ft_strncmp(line, "SO", 2) && ft_isspace(line[2]))
		return (parse_texture(line, &data->so));
	if (!ft_strncmp(line, "WE", 2) && ft_isspace(line[2]))
		return (parse_texture(line, &data->we));
	if (!ft_strncmp(line, "EA", 2) && ft_isspace(line[2]))
		return (parse_texture(line, &data->ea));
	if (line[0] == 'F' && ft_isspace(line[1]))
	{
		if (data->floor_set || parse_color(line + 1, data->floor))
			return (1);
		data->floor_set = 1;
		return (0);
	}
	if (line[0] == 'C' && ft_isspace(line[1]))
	{
		if (data->ceiling_set || parse_color(line + 1, data->ceiling))
			return (1);
		data->ceiling_set = 1;
		return (0);
	}
	return (1);
}

static char	*copy_map_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n'
			|| line[len - 1] == '\r'))
		len--;
	return (ft_substr(line, 0, len));
}

static int	add_map_line(t_data *data, char *line)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (data->map_height + 2));
	if (!new_map)
		return (1);
	i = 0;
	while (i < data->map_height)
	{
		new_map[i] = data->map[i];
		i++;
	}
	new_map[i] = copy_map_line(line);
	if (!new_map[i])
	{
		free(new_map);
		return (1);
	}
	new_map[i + 1] = NULL;
	free(data->map);
	data->map = new_map;
	data->map_height++;
	return (0);
}

int	parse_map(char *line, t_data *data)
{
	if (is_empty_line(line))
	{
		if (data->map_started)
			data->map_ended = 1;
		return (0);
	}
	if (!is_map_line(line))
		return (1);
	if (data->map_ended)
		return (1);
	data->map_started = 1;
	return (add_map_line(data, line));
}
