/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:08:29 by jaehpark          #+#    #+#             */
/*   Updated: 2020/11/25 02:58:07 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_str_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static void	*ft_free(char **s2, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free(s2[i]);
		i++;
	}
	free(s2);
	return (NULL);
}

static char	**ft_chr_count(char **s2, char const *s, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = -1;
	while (s[i])
	{
		count = 0;
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			j++;
			while (s[i] && s[i] != c)
			{
				count++;
				i++;
			}
			s2[j] = (char *)malloc(sizeof(char) * (count + 1));
			if (!s2[j])
				return (ft_free(s2, j - 1));
		}
	}
	return (s2);
}

static void	ft_strcpy(char **s2, char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = -1;
	while (s[i])
	{
		k = 0;
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			j++;
			while (s[i] && s[i] != c)
			{
				s2[j][k] = s[i];
				i++;
				k++;
			}
			s2[j][k] = '\0';
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**s2;
	int		count;

	if (!s)
		return (NULL);
	count = ft_str_count(s, c);
	s2 = (char **)malloc(sizeof(char *) * (count + 1));
	if (!s2)
		return (NULL);
	if (ft_chr_count(s2, s, c) == NULL)
		return (NULL);
	s2[count] = NULL;
	ft_strcpy(s2, s, c);
	return (s2);
}
