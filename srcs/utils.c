/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:15:27 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/25 23:11:21 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *msg)
{
	if (!msg)
		printf("bash: syntax error near unexpected token 'newline'\n");
	else if (msg[0] == '|' || msg[0] == '<' || msg[0] == '>')
		printf("bash: syntax error near unexpected token '%s'\n", msg);
	else
		printf("bash: %s: %s\n", msg, strerror(errno));
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
