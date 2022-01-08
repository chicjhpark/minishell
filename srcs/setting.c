/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 09:43:52 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/08 13:22:34 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_set(t_set *set)
{
	ft_memset(set, 0, sizeof(t_set));
	set->org_stdin = dup(STDIN_FILENO);
	set->org_stdout = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &set->org_term);
	tcgetattr(STDIN_FILENO, &set->new_term);
	set->new_term.c_lflag &= ~(ICANON);
	set->new_term.c_cc[VMIN] = 1;
	set->new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &set->new_term);
}

void	reset_set(t_set *set)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &set->org_term);
}

void	reset_stdio(t_set *set)
{
	dup2(set->org_stdin, STDIN_FILENO);
	dup2(set->org_stdout, STDOUT_FILENO);
}
