/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:13:03 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/01 20:48:35 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug(t_list *lst, char *name)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("%s [%d] : %s\n", name, i, (char *)lst->content);
		lst = lst->next;
		i++;
	}
}

void	get_input(void)
{
	char	*input;
	t_list	*token;

	input = readline("$ ");
	token = NULL;
	if (input)
	{
		if (split_token(input, &token) && check_token(token))
			parse_pipe_token(token);
	}
	ft_free(input);
	ft_lstclear(&token, free);
}

int	main(void)
{
	t_set	set;

	init_set(&set);
	while (1)
	{
		get_input();
		reset_set(&set);
	}
	return (0);
}
