/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:19:17 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/10 12:02:18 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug(t_list *lst, char *name)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("%s [%d] : %s!\n", name, i, (char *)lst->content);
		lst = lst->next;
		i++;
	}
}

int	parse_pipe(char *line, t_list **pipe)
{
	char	*save;
	char	*temp;
	int		i;

	save = line;
	i = -1;
	while (line[++i])
	{
		if (parse_quotation_mark(line, &i) == FALSE)
			return (FALSE);
		if (line[i] == '|')
		{
			temp = ft_strndup(line, i);
			if (temp == NULL)
				return (error_msg("malloc", 0));
			ft_lstadd_back(pipe, ft_lstnew(temp));
			line = &line[i + 1];
			if (!line[0])
				break ;
			i = -1;
		}
	}
	ft_lstadd_back(pipe, ft_lstnew(ft_strdup(line)));
	line = save;
	return (TRUE);
}

int	check_pipe(t_list *pipe)
{
	char	*temp;

	while (pipe)
	{
		temp = pipe->content;
		pipe->content = ft_strtrim(temp, " ");
		free(temp);
		temp = NULL;
		if (pipe->content[0] == '\0')
			return (error_msg(0, "|"));
		pipe = pipe->next;
	}
	return (TRUE);
}

void	handle_pipe(char *pipe)
{
	t_cmd	cmd;


}

void	parse_input(char *line)
{
	t_list	*pipe;

	pipe = NULL;
	if (parse_pipe(line, &pipe) == TRUE)
	{
		if (check_pipe(pipe) == TRUE)
		{
			while (pipe)
			{
				handle_pipe(pipe->content);
				pipe = pipe->next;
			}
		}
	}
	debug(pipe, "pipe");
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
