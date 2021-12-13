/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:19:17 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/13 16:40:22 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug(t_list *lst, char *name)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("%s [%d] : %s.\n", name, i, (char *)lst->content);
		lst = lst->next;
		i++;
	}
}

void	handle_pipe(char *pipe)
{
	t_list	*input;
	t_info	info;
	char	*save;

	input = NULL;
	ft_memset(&info, 0, sizeof(t_info));
	save = pipe;
	if (parse_redirection(pipe, &input) == TRUE)
		if (check_redirection(input) == TRUE)
		{
			if (handle_redirection(input, &info, &info.cmd) == TRUE)
			{}
		}
	pipe = save;
	debug(input, "input");
	//debug(info.cmd, "cmd");
	ft_lstclear(&input, free);
}

void	parse_input(char *line)
{
	t_list	*pipe;
	t_list	*head;

	pipe = NULL;
	if (parse_pipe(line, &pipe) == TRUE)
	{
		head = pipe;
		if (check_pipe(pipe) == TRUE)
			while (pipe)
			{
				handle_pipe(pipe->content);
				pipe = pipe->next;
			}
		pipe = head;
	}
	//debug(input, "pipe");
	ft_lstclear(&pipe, free);
}

void	get_input(void)
{
	char	*line;

	line = readline("$ ");
	if (line)
	{
		parse_input(line);
	}
	free(line);
	line = NULL;
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
