/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:08 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/05 06:08:00 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("cmd [%d] : %s\n", i, (char *)lst->content);
		lst = lst->next;
		i++;
	}
}

int	check_redirection(t_cmd *cmd, t_list *lst)
{
	char	*temp;

	while (lst)
	{
		if ((lst->content[0] == '<' || lst->content[0] == '>') && lst->next)
		{
			if ((lst->content[0] == '<' && lst->content[1] == '>') ||
			(lst->content[0] == '>' && lst->content[1] == '<') ||
			ft_strlen(lst->content) > 2)
				return (error_msg(0, &lst->content[1]));
			temp = lst->next->content;
			if (temp[0] == '<' || temp[0] == '>')
				return (error_msg(0, temp));
		}
		if (ft_strncmp(lst->content, "<<", 3) == 0)
			cmd->limiter = temp;
		else if (ft_strncmp(lst->content, ">>", 3) == 0)
			cmd->outfile = temp;
		else if (lst->content[0] == '<')
			cmd->infile = temp;
		else if (lst->content[0] == '>')
			cmd->outfile = temp;
		lst = lst->next;
		system("leaks minishell");
	}
	return (TRUE);
}

int	handle_redirection(t_cmd *cmd, t_list *lst)
{
	if (check_redirection(cmd, lst) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	handle_pipe(char *inputs)
{
	t_cmd	cmd;
	char	**input;
	int		i;

	ft_memset(&cmd, 0, sizeof(t_cmd));
	input = ft_split(sort_redirection(inputs), ' ');
	if (!input)
	{
		free(input);
		input = NULL;
		error_msg("malloc failed", 0);
		return ;
	}
	i = -1;
	while (input[++i])
		ft_lstadd_back(&cmd.lst, ft_lstnew(ft_strdup(input[i])));
	ft_free(input);
	if (handle_redirection(&cmd, cmd.lst) == FALSE)
	{
		ft_lstclear(&cmd.lst, free);
		return ;
	}
	debug(cmd.lst);
	ft_lstclear(&cmd.lst, free);
}

void	parse_input(char *line)
{
	char	**inputs;
	int		i;

	inputs = ft_split(line, '|');
	i = -1;
	while (inputs[++i])
		handle_pipe(inputs[i]);
	ft_free(inputs);
}

void	get_input(void)
{
	char	*line;

	line = readline("$ ");
	//line = "<<<ls>>ls";
	if (line)
	{
		parse_input(line);
		//system("leaks minishell");
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
