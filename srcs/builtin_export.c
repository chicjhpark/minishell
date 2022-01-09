/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:01:00 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/09 23:38:02 by han_woori        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_key_syntax_error(char *s)
{
	write(2, "bash: export: `", 15);
	write(2, s, ft_strlen(s));
	write(2, "': not a valid identifier\n", 27);
	g_stat = 1;
	return (0);
}

int	export_key_syntax_check(char *s)
{
	int	i;

	i = -1;
	if (s[0] > 47 && s[0] < 58)
		return (export_key_syntax_error(s));
	while (s[++i])
	{
		if (s[i] == '_')
			continue ;
		if (!ft_isalnum(s[i]))
			return (export_key_syntax_error(s));
	}
	g_stat = 0;
	return (1);
}

void	reset_env_print_check(t_env *env_list)
{
	t_env	*i;

	i = env_list;
	while (i)
	{
		i->print_check = 0;
		i = i->next;
	}
}

void	print_env_in_order(t_env *env_list)
{
	t_env	*i;
	t_env	*j;

	i = env_list;
	while (i)
	{
		if (i->print_check == 1)
		{
			i = i->next;
			continue ;
		}
		j = i -> next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0 && j->print_check == 0)
				i = j;
			j = j->next;
		}
		printf("declare -x %s=\"%s\"\n", i->key, i->value);
		i->print_check = 1;
		i = env_list;
	}
	i = env_list;
	reset_env_print_check(env_list);
}

void	ft_export(char **dbuf, t_env *env_list, char **splits, t_env *temp)
{
	if (!dbuf[0])
	{
		g_stat = 0;
		return (print_env_in_order(env_list));
	}
	while (*dbuf)
	{
		splits = ft_split(*(dbuf++), '=');
		if (!splits[1] || !export_key_syntax_check(splits[0]))
			continue ;
		temp = env_dup_check(env_list, splits[0]);
		if (temp)
		{
			free(temp->value);
			temp->value = ft_strdup(splits[1]);
			ft_free_split(splits);
			continue ;
		}
		env_lstadd_back(&env_list, temp, splits[0], splits[1]);
		free(splits);
	}
	g_stat = 0;
}
