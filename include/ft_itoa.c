/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alozpola <alozpola@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 22:20:18 by alozpola          #+#    #+#             */
/*   Updated: 2025/06/19 22:55:49 by alozpola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int		i;
	long	n1;

	i = 1;
	n1 = n;
	if (n1 < 0)
	{
		n1 = n1 * -1;
		i++;
	}
	while (n1 / 10 != 0)
	{
		n1 = n1 / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*c;
	long	n1;

	i = length(n);
	c = malloc(i + 1);
	n1 = n;
	if (!c)
		return (NULL);
	c[i] = '\0';
	if (n1 < 0)
	{
		n1 = n1 * -1;
		c[0] = '-';
	}
	while (i > 0 && c[i - 1] != '-')
	{
		c[i - 1] = (n1 % 10) + '0';
		n1 = n1 / 10;
		i--;
	}
	return (c);
}
