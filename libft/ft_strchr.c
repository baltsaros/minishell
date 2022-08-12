/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:33:16 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/10 12:57:11 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	x;
	size_t			i;

	if (!s)
		return (NULL);
	str = (unsigned char *)s;
	x = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == x)
			return ((char *)str + i);
		++i;
	}
	if (str[i] == x)
		return ((char *)str + i);
	return (NULL);
}
