/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:13:03 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/07 01:42:39 by jaehpark         ###   ########.fr       */
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
	//input = ft_strdup("ls");
	token = NULL;
	if (input)
	{
		add_history(input);
		if (split_token(input, &token) == TRUE
			&& check_token(token) == TRUE)
			parse_pipe_token(token);
	}
	input = ft_free(input);
	ft_lstclear(&token, free);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_set	set;

	init_set(&set, envp);
	while (1)
	{
		get_input();
		reset_set(&set);
		//system("leaks minishell");
	}
	return (0);
}
