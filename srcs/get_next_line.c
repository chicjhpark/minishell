/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:20:27 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/09 05:42:09 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sum(char *line, char buf)
{
	int		size;
	char	*str;
	int		i;

	size = ft_strlen(line);
	str = (char *)malloc(sizeof(char) * (size + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] != 0)
	{
		str[i] = line[i];
		i++;
	}
	free(line);
	str[i++] = buf;
	str[i] = '\0';
	return (str);
}

int	get_next_line(char **line)
{
	char	buf;
	int		ret;

	*line = (char *)malloc(1);
	if (*line == NULL)
		return (-1);
	(*line)[0] = 0;
	ret = read(0, &buf, 1);
	while (buf != '\n' && buf != '\0')
	{
		*line = sum(*line, buf);
		if (*line == 0)
			return (-1);
		ret = read(0, &buf, 1);
	}
	if (buf == '\n')
		return (1);
	return (0);
}
