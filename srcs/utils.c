/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:15:27 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/08 09:49:14 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *msg)
{
	write(2, "bash: ", 6);
	if (!msg)
		write(2, "syntax error near unexpected token 'newline'", 44);
	else if (msg[0] == '|' || msg[0] == '<' || msg[0] == '>')
	{
		write(2, "syntax error near unexpected token ", 35);
		write(2, "'", 1);
		write(2, msg, ft_strlen(msg));
		write(2, "'", 1);
	}
	else
	{
		write(2, msg, ft_strlen(msg));
		if (ft_strncmp(strerror(errno), "Bad address", 12) == 0)
			write(2, ": command not found", 19);
		else
		{
			write(2, ": ", 2);
			write(2, strerror(errno), ft_strlen(strerror(errno)));
		}
	}
	write(2, "\n", 1);
	return (ERROR);
}

void	*ft_free(char *p)
{
	if (p)
	{
		free(p);
		p = NULL;
	}
	return (NULL);
}

void	*ft_free2(char **p)
{
	int	i;

	i = -1;
	while (p[++i])
	{
		if (p[i])
		{
			free(p[i]);
			p[i] = NULL;
		}
	}
	free(p[i]);
	free(p);
	return (NULL);
}

char	*ft_strntrim(char *s, char *set, int n)
{
	char	*temp;
	char	*temp2;
	int		i;

	temp = (char *)malloc(sizeof(char) * (n + 1));
	if (!temp)
		return (NULL);
	i = -1;
	while (s[++i] && i < n)
		temp[i] = s[i];
	temp[i] = 0;
	temp2 = ft_strtrim(temp, set);
	ft_free(temp);
	return (temp2);
}

char	*ft_strndup(char *s, int n)
{
	char	*temp;
	int		i;

	temp = (char *)malloc(sizeof(char) * (n + 1));
	if (!temp)
		return (NULL);
	i = -1;
	while (s[++i] && i < n)
		temp[i] = s[i];
	temp[i] = 0;
	return (temp);
}
