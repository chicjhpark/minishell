/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:19:17 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/14 16:13:59 by jaehpark         ###   ########.fr       */
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

/*void	handle_command(t_info *info, t_list **cmd)
{

}*/

char	*delete_quotation_mark(char *s)
{
	char	*temp;
	int		i;
	int		j;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (temp == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == '\"')
			while (s[++i] && s[i] != '\"')
				temp[j++] = s[i];
		else if (s[i] == '\'')
			while (s[++i] && s[i] != '\'')
				temp[j++] = s[i];
		else
			temp[j++] = s[i];
	}
	temp[j] = '\0';
	printf("temp : %s\n", temp);
	return (temp);
}

/*int	handle_redirection(t_info *info, t_list **cmd)
{
	ft_lstiter(info->infile, delete_quotation_mark);
	ft_lstiter(info->outfile, delete_quotation_mark);
	ft_lstiter(info->outfile_add, delete_quotation_mark);
	ft_lstiter(*cmd, delete_quotation_mark);
	return (TRUE);
}*/

void	handle_pipe(char *pipe)
{
	t_list	*input;
	t_info	info;
	char	*save;

	input = NULL;
	ft_memset(&info, 0, sizeof(t_info));
	save = pipe;
	if (parse_token(pipe, &input) == TRUE)
		if (check_redirection(input) == TRUE)
			if (parse_redirection(input, &info, &info.cmd) == TRUE)
				//if (handle_redirection(&info, &info.cmd) == TRUE)
				//handle_command(&info, &info.cmd);
	pipe = save;
	debug(info.infile, "infile");
	debug(info.outfile_add, "outfile_add");
	debug(info.outfile, "outfile");
	debug(info.cmd, "cmd");
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
