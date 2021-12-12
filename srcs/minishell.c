/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:19:17 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/12 11:52:17 by jaehpark         ###   ########.fr       */
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

int	check_redirection(t_list *temp, t_cmd *cmd, t_list **lst)
{
	while (temp)
	{
		cmd->limiter = 0;
		ft_lstlast(*lst);
		temp = temp->next;
	}
	return (TRUE);
}

void	handle_pipe(char *input)
{
	t_list	*temp;
	t_cmd	cmd;
	char	*save;

	temp = NULL;
	ft_memset(&cmd, 0, sizeof(t_cmd));
	save = input;
	if (parse_redirection(input, &temp) == TRUE)
	{
		if (check_redirection(temp, &cmd, &cmd.lst) == TRUE)
		{

		}
	}
	input = save;
	debug(temp, "cmd");
}

void	parse_input(char *line)
{
	t_list	*input;
	t_list	*head;

	input = NULL;
	if (parse_pipe(line, &input) == TRUE)
	{
		head = input;
		if (check_pipe(input) == TRUE)
		{
			while (input)
			{
				handle_pipe(input->content);
				input = input->next;
			}
		}
		input = head;
	}
	//debug(input, "pipe");
	ft_lstclear(&input, free);
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
