/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:15:27 by jaehpark          #+#    #+#             */
/*   Updated: 2021/11/25 10:26:15 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *msg)
{
	printf("%s : %s\n", msg, strerror(errno));
	return (FALSE);
}

void	free_set(t_set *set)
{
	int	i;

	i = -1;
	while (set->input[++i])
	{
		free(set->input[i]);
		set->input[i] = NULL;
	}
	free(set->input);
	set->input = NULL;
}

void	init_set(t_set *set)
{
	ft_memset(set, 0, sizeof(set));
	tcgetattr(0, &set->org_term);
	tcgetattr(0, &set->new_term);
	set->new_term.c_lflag &= ~(ICANON | ECHO);
	set->new_term.c_cc[VMIN] = 1;
	set->new_term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &set->new_term);
}
