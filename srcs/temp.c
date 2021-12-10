/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:08 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/07 12:42:32 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug(t_list *lst, t_list *cmd)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("lst [%d] : %s\n", i, (char *)lst->content);
		lst = lst->next;
		i++;
	}
	i = 0;
	while (cmd)
	{
		printf("cmd [%d] : %s\n", i, (char *)cmd->content);
		cmd = cmd->next;
		i++;
	}
}

int		error_msg(char *msg, char *type)
{
	if (!type)
		printf("bash: %s: %s\n", msg, strerror(errno));
	else if (!msg)
		printf("bash : syntax error near unexpected token '%s'\n", type);
	return (FALSE);
}

void	handle_dollor_sign(t_list *lst)
{
	lst = lst->next;
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
	//handle_dollor_sign(cmd.lst);
	handle_redirection(&cmd, cmd.lst);
	debug(cmd.lst, cmd.cmd);
	ft_lstclear(&cmd.lst, free);
}

int	parse_input(char *line)
{
	char	**inputs;
	int		i;

	inputs = ft_split(line, '|');
	if (!inputs)
	{
		free(inputs);
		inputs = NULL;
		error_msg("malloc failed", 0);
		return (FALSE);
	}
	i = -1;
	while (inputs[++i])
	{
		if (ft_strncmp(inputs[i], " ", 2) == 0)
			return (error_msg(0, "|"));
		handle_pipe(inputs[i]);
	}
	ft_free(inputs);
	return (TRUE);
}

void	get_input(void)
{
	char	*line;

	line = readline("$ ");
	//line = ">ls";
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
