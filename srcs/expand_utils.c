/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 06:42:15 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/09 06:43:16 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_pre_env_var(char *data, int start, char *new_data)
{
	char	*org_data;
	char	*temp;

	org_data = new_data;
	temp = ft_strndup(data, start);
	if (!temp)
		return (NULL);
	new_data = ft_strjoin(new_data, temp);
	ft_free(temp);
	ft_free(org_data);
	return (new_data);
}
