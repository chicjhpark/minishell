/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:48:15 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/10 11:48:20 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_quotation_mark(char *line, int *i)
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
	return (TRUE);
}
