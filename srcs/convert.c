/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:29:17 by whan              #+#    #+#             */
/*   Updated: 2022/01/09 23:29:42 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_lstsize(t_env *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

char	**convert_env_lst_to_dp(t_env *env)
{
	int		len;
	char	**envp;
	char	*join_env;
	char	*temp;
	int		i;

	len = ft_env_lstsize(env);
	envp = (char **)malloc(sizeof(char *) * len + 1);
	envp[len] = NULL;
	i = 0;
	while (len--)
	{
		temp = ft_strjoin(env->key, "=");
		join_env = ft_strjoin(temp, env->value);
		free(temp);
		envp[i++] = join_env;
		env = env->next;
	}
	return (envp);
}
