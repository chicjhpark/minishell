/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:10:36 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/14 19:32:55 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(char **))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(&lst->content);
		lst = lst->next;
	}
}
