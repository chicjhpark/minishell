/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:08 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/02 08:27:30 by jaehpark         ###   ########.fr       */
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

int	check_redirection(char content)
{
	if (content == '<')
		return (error_msg("syntax error near unexpected token '<'"));
	else if (content == '>')
		return (error_msg("syntax error near unexpected token '>'"));
	return (TRUE);
}

int	cut_redirection(t_list *lst, char *content, int idx)
{
	char	*temp;

	temp = NULL;

}

void	sort_redirection(t_cmd *cmd, t_list *lst)
{
	while (lst)
	{
		if (ft_strncmp("<<", lst->content, 2) == 0 && lst->content[2])
		{
			if (cut_redirection(lst, lst->content, 2) == FALSE)
				return (FALSE);
			ft_lstadd_front(&lst, ft_lstnew("<<"));
		}
		else if (lst->content[0] == '<' && lst->content[1])
		{
			ft_lstadd_front(&lst, ft_lstnew("<"));
		}
		else if (ft_strncmp(">>", lst->content, 2) == 0 && lst->content[2])
		{
			ft_lstadd_front(&lst, ft_lstnew(">>"));
		}
		else if (lst->content[0] == '>' && lst->content[1])
		{
			ft_lstadd_front(&lst, ft_lstnew(">"));
		}
		ft_lstdelone(lst, free);
	}
}

int	handle_redirection(t_cmd *cmd, t_list *lst)
{
	sort_redirection(cmd, lst);
	while (lst)
	{

	}
}

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
	if (handle_redirection(&cmd, cmd.lst) == FALSE)
		return (FALSE);
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
