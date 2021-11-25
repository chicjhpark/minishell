/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:31:14 by jaehpark          #+#    #+#             */
/*   Updated: 2020/11/22 19:21:58 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_startcheck(char const *s1, char const *set)
{
	int	start;
	int	check;

	start = 0;
	check = 0;
	while (s1[check] && ft_strchr(set, s1[check]))
	{
		if (check >= start)
			start = check + 1;
		check++;
	}
	return (start);
}

static int	ft_endcheck(char const *s1, char const *set)
{
	int	end;
	int	check;

	end = ft_strlen(s1);
	if (end == 0)
		return (end);
	check = end - 1;
	while (check >= 0 && s1[check] && ft_strchr(set, s1[check]))
	{
		if (check < end)
			end = check;
		check--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = ft_startcheck(s1, set);
	end = ft_endcheck(s1, set);
	if (start > end)
		end = start;
	s2 = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (start < end)
	{
		s2[i] = s1[start];
		start++;
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
