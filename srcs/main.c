/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:13:03 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/27 18:05:07 by jaehpark         ###   ########.fr       */
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

char	*del_quot_token(char *data) // malloc -> copy
{
	char	*temp;
	int		i;
	int		j;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(data) + 1));
	i = -1;
	j = 0;
	while (data[++i])
	{
		if (data[i] == '\"' || data[i] == '\'')
			if (i != find_valid_quot_point(data, i))
				i++;
		temp[j++] = data[i];
		if (!data[i])
			return (temp);
	}
	temp[j] = 0;
	return (temp);
}

/*int	handle_redirection(t_proc *proc, t_list *data)
{
	char	*temp;
	int		infile;

	while (data)
	{
		if (data->content[0] == '<' || data->content[0] == '>')
		{
			temp = NULL;
			temp = expand_data(data->next->content);
			if (!temp)
				return (error_msg("malloc"));
			if (ft_strncmp(data->content, "<<", 3) == 0)
				ft_lstadd_back(&proc->limiter, ft_lstnew(temp));
			else if (ft_strncmp(data->content, "<", 2) == 0)
			{
				infile = open(temp, O_RDONLY);
				if (infile < 0)
					return (error_msg(temp));
				dup2(infile, STDIN_FILENO);
				data = data->next;
			}
			else if (data->content[0] == '>')
			{
				if (data->content[1] == '>')
					proc->outfile = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					proc->outfile = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (proc->outfile < 0)
					return (error_msg(temp));
			}
		}
		else
		{
			data = data->next;
			continue ;
		}
		data = data->next->next;
	}
	return (TRUE);
}*/

int	handle_proc(t_proc *proc)
{
	if (handle_redirection(proc, proc->data) == TRUE)
	{
	}
	debug(proc->data, "data");
	ft_lstclear(&proc->limiter, free);
	ft_lstclear(&proc->cmd, free);
	ft_lstclear(&proc->data, free);
	return (TRUE);
}

void	get_input(void)
{
	char	*input;
	t_list	*token;

	input = readline("$ ");
	token = NULL;
	if (input)
	{
		if (split_token(input, &token) && check_token(token))
			split_process(token);
	}
	//debug(token, "token");
	ft_free(input);
	ft_lstclear(&token, free);
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
