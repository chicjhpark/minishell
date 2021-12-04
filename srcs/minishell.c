/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:08 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/04 20:29:11 by jaehpark         ###   ########.fr       */
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
			temp = lst->next->content;
		if (temp[0] == '<' || temp[0] == '>')
			return (error_msg(0, temp));
		if (ft_strncmp(lst->content, "<<", 3) == 0)
			cmd->limiter = temp;
		else if (ft_strncmp(lst->content, ">>", 3) == 0)
			cmd->outfile = temp;
		else if (lst->content[0] == '<')
			cmd->infile = temp;
		else if (lst->content[0] == '>')
			cmd->outfile = temp;
		lst = lst->next;
	}
	return (TRUE);
}

int	handle_redirection(t_cmd *cmd, t_list *lst)
{
	if (check_redirection(cmd, lst) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	handle_pipe(char *inputs)
{
	t_cmd	cmd;
	char	**input;
	int		i;

	ft_memset(&cmd, 0, sizeof(t_cmd));
	input = ft_split(sort_redirection(inputs), ' ');
	if (!input)
		return (error_msg("malloc failed", 0));
	i = -1;
	while (input[++i])
		ft_lstadd_back(&cmd.lst, ft_lstnew(ft_strdup(input[i])));
	if (handle_redirection(&cmd, cmd.lst) == FALSE)
	{
		ft_free(input);
		return (FALSE);
	}
	debug(cmd.lst);
	ft_lstclear(&cmd.lst, 0);
	ft_free(input);
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
		{
			ft_free(inputs);
			return (FALSE);
		}
	}
	ft_free(inputs);
	return (TRUE);
}

int	get_input(void)
{
	char	*line;

	line = readline("$ ");
	//line = "<<<ls>>ls";
	if (line)
	{
		if (parse_input(line) == FALSE)
		{
			free(line);
			line = NULL;
			return (FALSE);
		}
	}
	free(line);
	line = NULL;
	return (TRUE);
}

void	reset_set(t_set *set)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &set->org_term);
	dup2(set->org_stdin, STDIN_FILENO);
	close(set->org_stdin);
}

int	main(void)
{
	t_set	set;

	init_set(&set);
	while (1)
	{
		if (get_input() == FALSE)
		{
			reset_set(&set);
			return (1);
		}
		reset_set(&set);
	}
	return (0);
}
