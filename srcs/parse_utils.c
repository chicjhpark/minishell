/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:57:31 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/20 16:19:45 by jaehpark         ###   ########.fr       */
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
