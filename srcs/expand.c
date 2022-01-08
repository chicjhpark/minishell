/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 21:11:16 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/09 01:32:57 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_small_quot_token(char *data, int start, char **new_data)
{
	char	*org_data;
	char	*temp;
	int		end;

	org_data = *new_data;
	temp = NULL;
	end = find_valid_quot_point(data, start);
	temp = my_strtrim(data, start, end);
	if (!temp)
		return (NULL);
	*new_data = ft_strjoin(*new_data, temp);
	ft_free(org_data);
	ft_free(temp);
	if (!(*new_data))
		return (NULL);
	data = &data[end + 1];
	return (data);
}

char	*expand_env_var(t_proc *proc, char *data, int start, char **new_data)
{
	char	*org_data;
	char	*get_env;
	char	*temp;

	org_data = *new_data;
	temp = ft_strndup(data, start);
	if (!temp)
		return (NULL);
	*new_data = ft_strjoin(*new_data, temp);
	ft_free(temp);
	ft_free(org_data);
	if (!(*new_data))
		return (NULL);
	data = &data[start + 1];
	get_env = ft_strndup(data, find_valid_env_var_point(data));
	data = &data[find_valid_env_var_point(data)];
	if (!get_env)
		return (ft_free(*new_data));
	temp = get_env;
	if (get_env[0] == '?')
		get_env = ft_itoa(g_stat);
	else
		get_env = read_value_of_key(proc->env_lst, get_env);
	ft_free(temp);
	*new_data = ft_strjoin(*new_data, get_env);
	if (*new_data)
		return (NULL);
	ft_free(get_env);
	return (data);
}

char	*expand_in_quot_env_var(t_proc *proc, char *data, int start, int end, int i)
{
	char	*new_data;
	char	*temp;

	new_data = ft_strndup(data, start);
	if (!new_data)
		return (NULL);
	data = &data[start + 1];
	data = ft_strndup(data, end - start - 1);
	if (!data)
		return (ft_free(new_data));
	i = -1;
	while (data[++i])
	{
		if (data[i] == '$')
		{
			data = expand_env_var(proc, data, i, &new_data);
			if (!data)
				return (ft_free(new_data));
			i = -1;
		}
	}
	temp = new_data;
	new_data = ft_strjoin(new_data, data);
	ft_free(temp);
	return (new_data);
}

char	*del_big_quot_token(t_proc *proc, char *data, int start, char **new_data)
{
	char	*org_data;
	char	*temp;
	int		end;

	org_data = *new_data;
	temp = NULL;
	end = find_valid_quot_point(data, start);
	if (find_env_var_token(data, start, end) == TRUE)
		temp = expand_in_quot_env_var(proc, data, start, end, -1);
	else
		temp = my_strtrim(data, start, end);
	if (!temp)
		return (NULL);
	*new_data = ft_strjoin(*new_data, temp);
	ft_free(org_data);
	ft_free(temp);
	if (!(*new_data))
		return (NULL);
	data = &data[end + 1];
	return (data);
}

char	*expand_data(t_proc *proc, char *data)
{
	char	*new_data;
	char	*temp;
	int		i;

	new_data = NULL;
	i = -1;
	while (data[++i])
	{
		if (data[i] == '\'' && i != find_valid_quot_point(data, i))
			data = del_small_quot_token(data, i, &new_data);
		else if (data[i] == '\"' && i != find_valid_quot_point(data, i))
			data = del_big_quot_token(proc, data, i, &new_data);
		else if (data[i] == '$')
			data = expand_env_var(proc, data, i, &new_data);
		else
			continue ;
		if (!data)
			return (ft_free(new_data));
		i = -1;
	}
	temp = new_data;
	new_data = ft_strjoin(new_data, data);
	ft_free(temp);
	return (new_data);
}
