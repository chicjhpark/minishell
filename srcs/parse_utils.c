/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:48:15 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/11 09:08:26 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_special_mark(char *input, int *i)
{
	if (input[*i] == '\"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\"')
			(*i)++;
		if (!input[*i])
			return (error_msg(0, "\""));
	}
	else if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (!input[*i])
			return (error_msg(0, "\'"));
	}
	else if (input[*i] == ';')
		return (error_msg(0, ";"));
	else if (input[*i] == '\\')
		return (error_msg(0, "\\"));
	return (TRUE);
}
