/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 21:11:16 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/04 09:42:02 by jaehpark         ###   ########.fr       */
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

char	*expand_env_var(char *data, int start, char **new_data)
{
	char	*org_data;
	char	*get_env;
	char	*temp;

	org_data = *new_data;
	temp = ft_strndup(data, start); // 환경 변수 전 문자열 저장
	if (!temp)
		return (NULL);
	*new_data = ft_strjoin(*new_data, temp); // 원본 문자열과 환경 변수 전 문자열 병합
	ft_free(temp);
	ft_free(org_data);
	if (!(*new_data))
		return (NULL);
	data = &data[start + 1]; // 달러 사인 이후 문자열 인덱스
	get_env = ft_strndup(data, find_valid_env_var_point(data));
	data = &data[find_valid_env_var_point(data)];
	if (!get_env)
		return (ft_free(*new_data));
	temp = get_env;
	get_env = getenv(get_env);
	ft_free(temp);
	*new_data = ft_strjoin(*new_data, get_env);
	return (data);
}

char	*expand_in_quot_env_var(char *data, int start, int end)
{
	char	*new_data;
	char	*temp;
	int		i;

	new_data = ft_strndup(data, start); // 쿼트 전 문자열 저장
	if (!new_data)
		return (NULL);
	data = &data[start + 1];
	data = ft_strndup(data, end - start - 1); // 쿼트 안쪽 문자열 한칸 증가 시켜서 인덱스를 저장 했기에 한칸 빼줌
	if (!data)
		return (ft_free(new_data));
	i = -1;
	while (data[++i])
		if (data[i] == '$')
		{
			data = expand_env_var(data, i, &new_data); // 환경 변수 확장
			if (!data)
				return (ft_free(new_data));
			i = -1;
		}
	temp = new_data;
	new_data = ft_strjoin(new_data, data); // 확장된 문자열과 남은 문자열 병합
	ft_free(temp);
	return (new_data);
}

char	*del_big_quot_token(char *data, int start, char **new_data)
{
	char	*org_data;
	char	*temp;
	int		end;

	org_data = *new_data;
	temp = NULL;
	end = find_valid_quot_point(data, start);
	if (find_env_var_token(data, start, end) == TRUE)
		temp = expand_in_quot_env_var(data, start, end);
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

char	*expand_data(char *data)
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
			data = del_big_quot_token(data, i, &new_data);
		else if (data[i] == '$')
			data = expand_env_var(data, i, &new_data);
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
