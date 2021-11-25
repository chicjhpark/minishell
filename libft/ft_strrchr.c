/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 11:34:47 by jaehpark          #+#    #+#             */
/*   Updated: 2021/11/25 09:57:31 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	int		end;

	cc = (char)c;
	end = ft_strlen(s);
	if (cc == '\0')
		return ((char *)&s[end]);
	while (end--)
		if (s[end] == cc)
		{
			if (end != 0 && s[end - 1] == cc)
				return ((char *)&s[end - 1]);
			return ((char *)&s[end]);
		}
	return (NULL);
}
