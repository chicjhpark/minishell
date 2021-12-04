/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:15:27 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/04 20:16:48 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *msg, char *type)
{
	if (!type)
		printf("bash : %s : %s\n", strerror(errno), msg);
	else if (!msg)
		printf("bash : syntax error near unexpected token '%s'\n", type);
	return (FALSE);
}

void	ft_free(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
	}
	free(ptr[i]);
	free(ptr);
	ptr = NULL;
}

void	init_set(t_set *set)
{
	ft_memset(set, 0, sizeof(t_set));
	set->org_stdin = dup(STDIN_FILENO);
	set->org_stdout = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &set->org_term);
	tcgetattr(STDIN_FILENO, &set->new_term);
	set->new_term.c_lflag &= ~(ICANON | ECHO);
	set->new_term.c_cc[VMIN] = 1;
	set->new_term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &set->new_term);
}
