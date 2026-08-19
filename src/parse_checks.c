/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 17:36:19 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/19 20:33:51 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	skip_whitespace(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int	empty_line_checker(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	map_line_checker(char *line)
{
	int	i;

	i = 0;
	i = skip_whitespace(line, i);
	if (!line[i] || line[i] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr(" 01NSEW", line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	extension_checker(char *file, char *ext)
{
	int	len_file;
	int	len_ext;

	len_file = ft_strlen(file);
	len_ext = ft_strlen(ext);
	if (len_file <= len_ext)
		return (0);
	return (!ft_strncmp(file + len_file - len_ext, ext, len_ext));
}
