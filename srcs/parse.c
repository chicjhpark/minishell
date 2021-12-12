/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:06:39 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/12 11:09:58 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe(char *line, t_list **input)
{
	char	*save;
	int		i;

	save = line;
	i = -1;
	while (line[++i])
	{
		if (parse_special_mark(line, &i) == FALSE)
			return (FALSE);
		if (line[i] == '|')
		{
			ft_lstadd_back(input, ft_lstnew(ft_strndup(line, i)));
			line = &line[i + 1];
			if (!line[0])
				break ;
			i = -1;
		}
	}
	ft_lstadd_back(input, ft_lstnew(ft_strdup(line)));
	line = save;
	return (TRUE);
}

int	check_pipe(t_list *input)
{
	char	*temp;

	while (input)
	{
		temp = input->content;
		input->content = ft_strtrim(temp, " ");
		free(temp);
		temp = NULL;
		if (input->content[0] == '\0')
			return (error_msg(0, "|"));
		input = input->next;
	}
	return (TRUE);
}

int	parse_redirection(char *input, t_list **temp)
{
	int		i;

	i = -1;
	while (input[++i])
	{
		if (parse_special_mark(input, &i) == FALSE)
			return (FALSE);
		if (input[i] == '<' || input[i] == '>')
		{
			if (i != 0)
				ft_lstadd_back(temp, ft_lstnew(ft_strndup(input, i)));
			input = &input[i];
			i = 0;
			while (input[i] && (input[i] == '<' || input[i] == '>'))
				i++;
			ft_lstadd_back(temp, ft_lstnew(ft_strndup(input, i)));
			input = &input[i];
			if (!input[0])
				break ;
			i = -1;
		}
	}
	ft_lstadd_back(temp, ft_lstnew(ft_strdup(input)));
	return (TRUE);
}
