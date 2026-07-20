/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alozpola <alozpola@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:58:22 by alozpola          #+#    #+#             */
/*   Updated: 2025/06/19 22:58:11 by alozpola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (size == 0)
		return (ft_strlen(src));
	i = ft_strlen(dst);
	j = i;
	k = 0;
	if (size <= i)
		return (size + ft_strlen(src));
	while (src[k] != '\0' && i < size - 1)
	{
		dst[i] = src[k];
		k++;
		i++;
	}
	dst[i] = '\0';
	return (j + ft_strlen(src));
}
