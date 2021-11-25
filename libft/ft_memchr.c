/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:55:36 by jaehpark          #+#    #+#             */
/*   Updated: 2020/11/16 20:34:01 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*uc_s;
	unsigned char		uc_c;
	size_t				i;

	uc_s = (const unsigned char *)s;
	uc_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (uc_s[i] == uc_c)
			return ((void *)&s[i]);
		i++;
	}
	return (NULL);
}
