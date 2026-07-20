/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alozpola <alozpola@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:42:28 by alozpola          #+#    #+#             */
/*   Updated: 2025/06/19 22:55:34 by alozpola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*ptr;

	total = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	ptr = malloc(total);
	if (ptr == NULL)
	{
		return (0);
	}
	ft_memset(ptr, 0, total);
	return (ptr);
}
