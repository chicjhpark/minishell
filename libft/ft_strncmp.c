/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:45:38 by jaehpark          #+#    #+#             */
/*   Updated: 2020/11/18 15:12:35 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*uc_s1;
	const unsigned char	*uc_s2;
	size_t				i;

	uc_s1 = (const unsigned char *)s1;
	uc_s2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if ((uc_s1[i] > uc_s2[i]) || (uc_s1[i] && !uc_s2[i]))
			return (1);
		else if ((uc_s1[i] < uc_s2[i]) || (!uc_s1[i] && uc_s2[i]))
			return (-1);
		else if (!uc_s1[i] && !uc_s2[i])
			return (0);
		i++;
	}
	return (0);
}
