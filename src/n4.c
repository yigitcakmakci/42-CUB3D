/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n4.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alozpola <alozpola@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:35:09 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 17:35:10 by alozpola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

static int	process_line(char *line, t_data *data)
{
	if (data->map_started)
		return (parse_map(line, data));
	if (is_empty_line(line))
		return (0);
	if (is_map_line(line))
	{
		if (!data->no || !data->so || !data->we || !data->ea
			|| !data->floor_set || !data->ceiling_set)
			return (1);
		return (parse_map(line, data));
	}
	return (parse_config(line, data));
}

static int	read_file(int fd, t_data *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (process_line(line, data))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_file(char *file, t_data *data)
{
	int	fd;

	if (!check_extension(file, ".cub"))
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (read_file(fd, data))
	{
		close(fd);
		free_data(data);
		return (1);
	}
	close(fd);
	if ((!data->no || !data->so || !data->we || !data->ea
			|| !data->floor_set || !data->ceiling_set) || validate_map(data))
	{
		free_data(data);
		return (1);
	}
	return (0);
}

static char	*expand_line(char *line, int width)
{
	char	*new;
	int		i;
	int		len;

	len = ft_strlen(line);
	new = malloc(sizeof(char) * (width + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = line[i];
		i++;
	}
	while (i < width)
	{
		new[i] = ' ';
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	normalize_map(t_data *data)
{
	char	*new_line;
	int		i;
	int		max;

	i = 0;
	max = 0;
	while (i < data->map_height)
	{
		if (ft_strlen(data->map[i]) > max)
			max = ft_strlen(data->map[i]);
		i++;
	}
	data->map_width = max;
	i = 0;
	while (i < data->map_height)
	{
		new_line = expand_line(data->map[i], data->map_width);
		if (!new_line)
			return (1);
		free(data->map[i]);
		data->map[i] = new_line;
		i++;
	}
	return (0);
}
