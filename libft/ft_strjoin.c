/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:00:42 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/24 02:40:56 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		l1;
	int		l2;

	if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	l1 = 0;
	while (s1[l1])
	{
		s3[l1] = s1[l1];
		l1++;
	}
	l2 = 0;
	while (s2[l2])
	{
		s3[l1 + l2] = s2[l2];
		l2++;
	}
	s3[l1 + l2] = 0;
	return (s3);
}
