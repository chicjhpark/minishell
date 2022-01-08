/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:02:17 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/09 01:05:08 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_value_of_key(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, key))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

int	ft_echo(char **buf)
{
	int	i;

	i = 0;
	while (buf[i + 1] != NULL && !ft_strcmp(buf[i + 1], "-n"))
	{
		i++;
		if (buf[i + 1] == NULL)
			break ;
	}
	while (buf[i])
	{
		printf("%s", buf[i]);
		if (buf[i++ + 1] != 0)
			printf(" ");
	}
	if ((i == 1) || (i > 1 && ft_strcmp(buf[0], "-n") != 0))
		printf("\n");
	g_stat = 0;
	return (0);
}

void	ft_pwd(void)
{
	char	pbuf[4096];

	getcwd(pbuf, 4096);
	printf("%s\n", pbuf);
	g_stat = 0;
}
