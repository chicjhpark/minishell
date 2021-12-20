/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:48:15 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/13 21:52:43 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special_mark(char *line, int *i)
{
	if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\"')
			(*i)++;
		if (!line[*i])
			return (error_msg(0, "\""));
	}
	else if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (!line[*i])
			return (error_msg(0, "\'"));
	}
	else if (line[*i] == ';')
		return (error_msg(0, ";"));
	else if (line[*i] == '\\')
		return (error_msg(0, "\\"));
	return (TRUE);
}

void	skip_quotation_mark(char *line, int *i)
{
	if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\"')
			(*i)++;
	}
	else if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
	}
}

void	skip_space(char **pipe, int *i, t_list **input)
{
	if ((*pipe)[*i] == ' ')
	{
		if (*i != 0)
			ft_lstadd_back(input, ft_lstnew(ft_strndup(*pipe, *i)));
		while ((*pipe)[*i] && (*pipe)[*i] == ' ')
			(*i)++;
		(*pipe) = &(*pipe)[*i];
		*i = 0;
	}
	skip_quotation_mark(*pipe, i);
}
