/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <mavin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:31:54 by jaehpark          #+#    #+#             */
/*   Updated: 2020/11/16 20:31:19 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*uc_b;
	unsigned char	uc_c;
	size_t			i;

	uc_b = (unsigned char *)b;
	uc_c = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		uc_b[i] = uc_c;
		i++;
	}
	return (b);
}
