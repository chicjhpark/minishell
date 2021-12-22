/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:00:42 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/22 17:18:29 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		l1;
	int		l2;

	if (!s1)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
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
