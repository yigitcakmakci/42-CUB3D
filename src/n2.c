/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:36:08 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 23:22:07 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

static char	*get_path(char *line)
{
	int		i;
	int		start;
	char	*path;

	i = 2;
	i = skip_spaces(line, i);
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	while (i > start && (line[i - 1] == ' ' || line[i - 1] == '\t'))
		i--;
	path = ft_substr(line, start, i - start);
	return (path);
}

int	parse_texture(char *line, char **dst)
{
	char	*path;
	int		fd;

	if (*dst)
		return (1);
	path = get_path(line);
	if (!path || !*path)
	{
		free(path);
		return (1);
	}
	if (!check_extension(path, ".xpm") && !check_extension(path, ".XPM"))
	{
		free(path);
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		return (1);
	}
	close(fd);
	*dst = path;
	return (0);
}

static int	parse_number(char **str, int *value)
{
	long	n;

	*str += skip_spaces(*str, 0);
	if (!ft_isdigit(**str))
		return (1);
	n = 0;
	while (ft_isdigit(**str))
	{
		if (n > 255)
			return (1);
		n = n * 10 + (**str - '0');
		(*str)++;
	}
	if (n < 0 || n > 255)
		return (1);
	*value = n;
	*str += skip_spaces(*str, 0);
	return (0);
}

int	parse_color(char *str, int color[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (parse_number(&str, &color[i]))
			return (1);
		if (i < 2)
		{
			if (*str != ',')
				return (1);
			str++;
		}
		i++;
	}
	str += skip_spaces(str, 0);
	if (*str && *str != '\n' && *str != '\r')
		return (1);
	return (0);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->map)
		free_map(data->map);
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->floor_set = 0;
	data->ceiling_set = 0;
	data->map_started = 0;
	data->map_ended = 0;
}
