/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:15:27 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/10 10:34:01 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_msg(char *msg, char *type)
{
	if (!type)
		printf("bash: %s: %s\n", msg, strerror(errno));
	else if (!msg)
		printf("bash : syntax error near unexpected token '%s'\n", type);
	return (FALSE);
}

char	*ft_strndup(char *s, int n)
{
	char	*s2;
	int		i;

	s2 = (char *)malloc(sizeof(char) * (n + 1));
	if (s2 == NULL)
		return (NULL);
	i = -1;
	while (s[++i] && i < n)
		s2[i] = s[i];
	s2[i] = '\0';
	return (s2);
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

void	reset_set(t_set *set)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &set->org_term);
	dup2(set->org_stdin, STDIN_FILENO);
	//close(set->org_stdin);
}
