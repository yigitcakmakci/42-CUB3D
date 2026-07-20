/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alozpola <alozpola@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:46:23 by alozpola          #+#    #+#             */
/*   Updated: 2025/06/19 22:58:27 by alozpola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			size;
	unsigned int	i;
	char			*mapi;

	if (!s || !f)
		return (NULL);
	size = ft_strlen(s);
	i = 0;
	mapi = malloc(size + 1);
	if (!mapi)
		return (NULL);
	while (i < size)
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	mapi[size] = '\0';
	return (mapi);
}
