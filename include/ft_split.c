/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alozpola <alozpola@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 21:58:59 by alozpola          #+#    #+#             */
/*   Updated: 2025/06/23 21:56:00 by alozpola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

static char	*create(const char *start, size_t len)
{
	char	*a;

	a = malloc(len + 1);
	if (!a)
		return (NULL);
	ft_strlcpy(a, start, len + 1);
	return (a);
}

static char	**free_all(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free(arr);
	return (NULL);
}

static char	**isle(char const *s, char c)
{
	char		**res;
	size_t		i;
	const char	*end;

	i = 0;
	res = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		end = s;
		while (*end && *end != c)
			end++;
		if ((end - s) != 0)
		{
			res[i++] = create(s, end - s);
			if (!res[i - 1])
				return (free_all(res, i - 1));
		}
		s = end;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = isle(s, c);
	return (res);
}
