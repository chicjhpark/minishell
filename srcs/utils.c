/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:15:27 by jaehpark          #+#    #+#             */
/*   Updated: 2021/11/30 19:34:02 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *msg)
{
	printf("%s : %s\n", msg, strerror(errno));
	return (FALSE);
}

void	ft_free(char **p)
{
	int	i;

	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
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
