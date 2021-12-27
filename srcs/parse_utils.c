/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:57:31 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/26 15:34:53 by jaehpark         ###   ########.fr       */
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
