/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 21:16:03 by jaehpark          #+#    #+#             */
/*   Updated: 2020/11/24 00:05:15 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_compt(int n, int fd)
{
	char	temp;

	if (n < 0 && n > -10)
		temp = (n * -1) + '0';
	else if (n < 0)
	{
		temp = ((n % 10) * -1) + '0';
		n = n / -10;
		ft_compt(n, fd);
	}
	else if (n >= 10)
	{
		temp = (n % 10) + '0';
		n = n / 10;
		ft_compt(n, fd);
	}
	else
		temp = n + '0';
	write(fd, &temp, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write(fd, "-", 1);
	ft_compt(n, fd);
}
