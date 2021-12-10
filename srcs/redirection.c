/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:47:53 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/07 12:31:39 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirection(t_cmd *cmd, t_list *lst)
{
	if (check_redirection(lst) == FALSE)
		return (FALSE);
	if (init_redirection(cmd, lst) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	init_redirection(t_cmd *cmd, t_list *lst)
{
	char	*temp;
	int		infile;

	while (lst)
	{
		if (lst->next)
		{
			temp = lst->next->content;
			if (ft_strncmp(lst->content, "<<", 2) == 0)
				cmd->limiter = temp;
			else if (ft_strncmp(lst->content, ">>", 2) == 0)
			{
				cmd->outfile = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (cmd->outfile < 0)
					return (error_msg(temp, 0));
			}
			else if (lst->content[0] == '<')
			{
				infile = open(temp, O_RDONLY);
				if (infile < 0)
					return (error_msg(temp, 0));
				dup2(infile, STDIN_FILENO);
			}
			else if (lst->content[0] == '>')
			{
				cmd->outfile = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (cmd->outfile < 0)
					return (error_msg(temp, 0));
			}
			else
				lst = lst->next;
		}
		ft_lstadd_back(&cmd->cmd, ft_lstnew(lst->content));
		lst = lst->next;
	}
	return (TRUE);
}

int	check_redirection(t_list *lst)
{
	char	*temp;

	while (lst)
	{
		if (lst->content[0] == '<' || lst->content[0] == '>')
		{
			if ((lst->content[0] == '<' && lst->content[1] == '>') ||
			(lst->content[0] == '>' && lst->content[1] == '<'))
				return (error_msg(0, &lst->content[1]));
			else if (ft_strlen(lst->content) > 2)
				return (error_msg(0, &lst->content[2]));
			if (lst->next)
			{
				temp = lst->next->content;
				if (temp[0] == '<' || temp[0] == '>')
					return (error_msg(0, temp));
			}
			else
				return (error_msg(0, "new line"));
		}
		lst = lst->next;
	}
	return (TRUE);
}

void	divide_redirection(char *inputs, char *temp)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (inputs[++i])
	{
		if (inputs[i] == '<' || inputs[i] == '>')
		{
			if (i > 0 && inputs[i - 1] != '<' && inputs[i - 1] != '>')
				temp[i + j++] = ' ';
			if (inputs[i + 1] != '<' && inputs[i + 1] != '>')
			{
				temp[i + j++] = inputs[i];
				temp[i + j] = ' ';
				continue ;
			}
		}
		temp[i + j] = inputs[i];
	}
	temp[i + j] = '\0';
}

char	*sort_redirection(char *inputs)
{
	char	*temp;
	int		count;
	int		i;

	i = -1;
	count = 0;
	while (inputs[++i])
		if (inputs[i] == '<' || inputs[i] == '>')
			count++;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(inputs) + count * 2 + 1));
	if (!temp)
		return (NULL);
	divide_redirection(inputs, temp);
	return (temp);
}
