/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zget_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:43:58 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 23:26:30 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

static char	*split(char *c)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!c || !*c)
		return (NULL);
	i = 0;
	j = 0;
	while (c[i] && c[i] != '\n')
		i++;
	if (c[i] == '\n')
		j = 1;
	new_str = malloc(i + j + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (c[i] && c[i] != '\n')
	{
		new_str[i] = c[i];
		i++;
	}
	if (c[i] == '\n')
		new_str[i++] = '\n';
	new_str[i] = '\0';
	return (new_str);
}

static char	*update(char *c)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	while (c[i] && c[i] != '\n')
		i++;
	if (!c[i])
	{
		free(c);
		return (NULL);
	}
	i++;
	temp = malloc(ft_strlen(c) - i + 1);
	if (!temp)
	{
		free(c);
		return (NULL);
	}
	j = 0;
	while (c[i])
		temp[j++] = c[i++];
	temp[j] = '\0';
	free(c);
	return (temp);
}

static char	*add(char *a, char *b)
{
	char	*c;
	int		i;
	int		j;

	j = ft_strlen(a);
	c = malloc(j + ft_strlen(b) + 1);
	if (!c)
		return (NULL);
	i = 0;
	while (i < j)
	{
		c[i] = a[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(b))
	{
		c[j + i] = b[i];
		i++;
	}
	c[j + ft_strlen(b)] = '\0';
	free(a);
	return (c);
}

static char	*execute(int fd, char *left_str)
{
	char	*buff;
	ssize_t	rd_bytes;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (!left_str)
		left_str = ft_strdup("");
	rd_bytes = 1;
	while (left_str && !ft_strchr(left_str, '\n') && rd_bytes > 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes < 0)
		{
			free(buff);
			free(left_str);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = add(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left_str = execute(fd, left_str);
	if (!left_str)
		return (NULL);
	line = split(left_str);
	left_str = update(left_str);
	return (line);
}