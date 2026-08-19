/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n4.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:35:09 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 23:22:07 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

static int	process_line(char *line, t_data *data)
{
	if (data->map_started)
		return (map_parser(line, data));
	if (empty_line_checker(line))
		return (0);
	if (map_line_checker(line))
	{
		if (!data->no || !data->so || !data->we || !data->ea
			|| !data->floor_set || !data->ceiling_set)
			return (1);
		return (map_parser(line, data));
	}
	return (main_parser(line, data));
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

int	file_opener(char *file, t_data *data)
{
	int	fd;

	if (!extension_checker(file, ".cub"))
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

static char	*expand_lines(char *line, int width)
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
		new_line = expand_lines(data->map[i], data->map_width);
		if (!new_line)
			return (1);
		free(data->map[i]);
		data->map[i] = new_line;
		i++;
	}
	return (0);
}
