/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:57:31 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/28 09:12:02 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_valid_quot_point(char *line, int start)
{
	int	find;

	find = start + 1;
	while (line[find] && line[start] != line[find])
		find++;
	if (line[find])
		return (find);
	return (start);
}

int	find_env_var_point(char *line)
{
	int	find;

	find = 0;
	while (line[find] && (line[find] == '_' || ft_isalnum(line[find])))
		find++;
	return (find);
}

int	check_token(t_list *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->content[0] == '|' && (i == 0 ||
			!token->next || token->next->content[0] == '|'))
			return (error_msg("|"));
		else if (token->content[0] == '<' || token->content[0] == '>')
		{
			if (token->content[1] && token->content[0] != token->content[1])
				return (error_msg(&token->content[1]));
			else if (ft_strlen(token->content) > 2)
				return (error_msg(&token->content[2]));
			else if (!token->next)
				return (error_msg(NULL));
			else if (token->next->content[0] == '<' || token->next->content[0] == '>'
					|| token->next->content[0] == '|')
				return (error_msg(token->next->content));
		}
		i++;
		token = token->next;
	}
	return (TRUE);
}

char	*expand_env_var(char *data, int i)
{
	char	*temp;
	char	*pre_env_var;
	char	*get_env_var;
	char	*merge_env_var;
	char	*new_data;

	temp = ft_strndup(data, i);
	if (!temp)
		return (NULL);
	data = &data[i + 1];
	i = find_env_var_point(data);
	pre_env_var = ft_strndup(data, i);
	if (!pre_env_var)
		return (ft_free(temp));
	data = &data[i];
	get_env_var = getenv(pre_env_var);
	ft_free(pre_env_var);
	merge_env_var = ft_strjoin(temp, get_env_var);
	ft_free(temp);
	if (!merge_env_var)
		return (NULL);
	new_data = ft_strjoin(merge_env_var, data);
	ft_free(merge_env_var);
	return (new_data);
}
