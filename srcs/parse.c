/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:58:37 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/21 11:50:59 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
