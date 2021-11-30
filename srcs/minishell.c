/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:08 by jaehpark          #+#    #+#             */
/*   Updated: 2021/11/30 20:20:55 by jaehpark         ###   ########.fr       */
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

/*int	handle_redirection(t_cmds *cmds, t_list *cmd)
{
	while (cmd->content)
	{

	}
}*/

int	handle_pipe(char *inputs)
{
	t_cmd	cmd;
	char	**input;
	int		i;

	ft_memset(&cmd, 0, sizeof(cmd));
	input = ft_split(inputs, ' ');
	i = -1;
	while (input[++i])
		ft_lstadd_back(&cmd.lst, ft_lstnew(input[i]));
	/*if (handle_redirection(&cmds, &cmds.cmd) == FALSE)
		return (FALSE);*/
	debug(cmd.lst);
	ft_lstclear(&cmd.lst, free);
	return (TRUE);
}

int	parse_input(char *line)
{
	char	**inputs;
	int		i;

	inputs = ft_split(line, '|');
	i = -1;
	while (inputs[++i])
	{
		if (handle_pipe(inputs[i]) == FALSE)
			return (FALSE);
		free(inputs[i]);
	}
	free(inputs);
	return (TRUE);
}

int	get_input(void)
{
	char	*line;

	line = readline("$ ");
	if (line)
	{
		if (parse_input(line) == FALSE)
			return (FALSE);
	}
	free(line);
	return (TRUE);
}

int	main(void)
{
	t_set	set;

	init_set(&set);
	while (1)
	{
		if (get_input() == FALSE)
			break ;
	}
	return (0);
}
