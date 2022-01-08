/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:57:31 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/09 04:08:02 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strtrim(char *data, int start, int end)
{
	char	*temp;
	int		i;
	int		j;

	temp = (char *)malloc(sizeof(char) * end);
	if (!temp)
		return (NULL);
	i = -1;
	j = 0;
	while (data[++i] && i < end)
		if (i != start)
			temp[j++] = data[i];
	temp[j] = 0;
	return (temp);
}

int	find_valid_env_var_point(char *data)
{
	int	find;

	if (data[0] == '?')
		return (1);
	find = 0;
	while (data[find] && (ft_isalnum(data[find]) || data[find] == '_'))
		find++;
	return (find);
}

int	find_env_var_token(char *data, int start, int end)
{
	int	find;

	find = start + 1;
	while (data[find] && find < end && data[find] != '$')
		find++;
	if (!find)
		return (FALSE);
	return (TRUE);
}

int	find_valid_quot_point(char *data, int start)
{
	int	find;

	find = start + 1;
	while (data[find] && data[start] != data[find])
		find++;
	if (data[find])
		return (find);
	return (start);
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
			else if (token->next->content[0] == '<'
				|| token->next->content[0] == '>'
				|| token->next->content[0] == '|')
				return (error_msg(token->next->content));
		}
		i++;
		token = token->next;
	}
	return (TRUE);
}
