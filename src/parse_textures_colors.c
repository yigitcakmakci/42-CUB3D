/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_colors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:36:08 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/19 20:34:43 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "fcntl.h"

static char	*get_path(char *line)
{
	int		i;
	int		start;
	char	*path;

	i = 2;
	i = skip_whitespace(line, i);
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	while (i > start && (line[i - 1] == ' ' || line[i - 1] == '\t'))
		i--;
	path = ft_substr(line, start, i - start);
	return (path);
}

int	texture_parser(char *line, char **dst)
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
	if (!extension_checker(path, ".xpm") && !extension_checker(path, ".XPM"))
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

static int	number_parser(char **str, int *value)
{
	long	n;

	*str += skip_whitespace(*str, 0);
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
	*str += skip_whitespace(*str, 0);
	return (0);
}

int	color_parser(char *str, int color[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (number_parser(&str, &color[i]))
			return (1);
		if (i < 2)
		{
			if (*str != ',')
				return (1);
			str++;
		}
		i++;
	}
	str += skip_whitespace(str, 0);
	if (*str && *str != '\n' && *str != '\r')
		return (1);
	return (0);
}
