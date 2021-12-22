/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:30:52 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/20 21:36:06 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_redirection_token(char *input, int i, t_list **token)
{
	char	*temp;
	int		save;

	save = i;
	if (i != 0)
	{
		temp = ft_strntrim(input, " ", i);
		if (!temp)
			return (error_msg("malloc"));
		ft_lstadd_back(token, ft_lstnew(temp));
		input = &input[i];
		i = 0;
	}
	while (input[i] == '<' || input[i] == '>')
		i++;
	temp = ft_strntrim(input, " ", i);
	if (!temp)
		return (error_msg("malloc"));
	ft_lstadd_back(token, ft_lstnew(temp));
	return (i + save);
}

int	split_space_token(char *input, int i, t_list **token)
{
	char	*temp;

	if (i != 0)
	{
		temp = ft_strntrim(input, " ", i);
		if (!temp)
			return (error_msg("malloc"));
		ft_lstadd_back(token, ft_lstnew(temp));
	}
	while (input[i] == ' ')
		i++;
	return (i);
}

int	split_pipe_token(char *input, int i, t_list **token)
{
	char	*temp;

	if (i != 0)
	{
		temp = ft_strntrim(input, " ", i);
		if (!temp)
			return (error_msg("malloc"));
		ft_lstadd_back(token, ft_lstnew(temp));
	}
	temp = ft_strdup("|");
	if (!temp)
		return (error_msg("malloc"));
	ft_lstadd_back(token, ft_lstnew(temp));
	return (i + 1);
}

int	split_rest_token(char *input, t_list **token)
{
	char	*temp;

	if (input[0])
	{
		temp = ft_strntrim(input, " ", ft_strlen(input));
		if (!temp)
			return (error_msg("malloc"));
		ft_lstadd_back(token, ft_lstnew(temp));
	}
	return (TRUE);
}

int	split_token(char *input, t_list **token)
{
	int		i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			i = find_valid_quot_point(input, i);
			continue ;
		}
		else if (input[i] == '<' || input[i] == '>')
			i = split_redirection_token(input, i, token);
		else if (input[i] == ' ')
			i = split_space_token(input, i, token);
		else if (input[i] == '|')
			i = split_pipe_token(input, i, token);
		else
			continue ;
		if (i == ERROR)
			return (ERROR);
		input = &input[i];
		i = -1;
	}
	return (split_rest_token(input, token));
}
