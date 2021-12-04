/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:47:53 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/04 20:29:08 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	divide_redirection(char *inputs, char *temp)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (inputs[++i])
	{
		if (inputs[i] == '<' || inputs[i] == '>')
		{
			if (i > 0 && inputs[i - 1] != '<' && inputs[i - 1] != '>')
				temp[i + j++] = ' ';
			if (inputs[i + 1] != '<' && inputs[i + 1] != '>')
			{
				temp[i + j++] = inputs[i];
				temp[i + j] = ' ';
				continue ;
			}
		}
		temp[i + j] = inputs[i];
	}
	temp[i + j] = '\0';
}

char	*sort_redirection(char *inputs)
{
	char	*temp;
	int		count;
	int		i;

	i = -1;
	count = 0;
	while (inputs[++i])
		if (inputs[i] == '<' || inputs[i] == '>')
			count++;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(inputs) + count * 2 + 1));
	if (!temp)
		return (NULL);
	divide_redirection(inputs, temp);
	return (temp);
}
