/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:00:48 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/09 05:41:51 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_exit_arg(char	*arg)
{
	int	i;

	i = 0;
	if (ft_strlen(arg) > 18)
		return (0);
	if (arg[0] == '-' || arg[0] == '+' )
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i++]))
			return (0);
	}
	return (1);
}

int	exit_numeric_arg_cal(char *arg)
{
	int		res;

	res = ft_atoi(arg);
	if (res >= 0 && res < 255)
		return (res);
	else
		return (255);
}

void	exit_extra_cases(int c, char *s)
{
	if (c == 1)
	{
		printf("exit\n");
		write(2, "bash: exit: ", 12);
		write(2, s, ft_strlen(s));
		write(2, ": numeric argument required\n", 28);
		exit(255);
	}
	else
	{
		printf("exit\n");
		write(2, "bash: exit: too many arguments\n", 31);
		g_stat = 1;
	}
}

void	ft_exit(char **dbuf)
{
	if (!dbuf[0])
	{
		exit(0);
	}
	if (!valid_exit_arg(dbuf[0]))
		exit_extra_cases(1, dbuf[0]);
	else if (!dbuf[1])
	{
		printf("exit\n");
		exit(exit_numeric_arg_cal(dbuf[0]));
	}
	else
	{
		exit_extra_cases(2, NULL);
		return ;
	}
}
