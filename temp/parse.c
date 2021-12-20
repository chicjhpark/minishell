/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:06:39 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/15 06:07:55 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe(char *line, t_list **pipe)
{
	char	*save;
	int		i;

	save = line;
	i = -1;
	while (line[++i])
	{
		if (check_special_mark(line, &i) == FALSE)
			return (FALSE);
		if (line[i] == '|')
		{
			ft_lstadd_back(pipe, ft_lstnew(ft_strndup(line, i)));
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
		if (pipe->content == NULL)
			return (error_msg("malloc", 0));
		free(temp);
		temp = NULL;
		if (pipe->content[0] == '\0')
			return (error_msg(0, "|"));
		pipe = pipe->next;
	}
	return (TRUE);
}

int	parse_token(char *pipe, t_list **input)
{
	int	i;

	i = -1;
	while (pipe[++i])
	{
		skip_space(&pipe, &i, input);
		if (!pipe[0])
				break ;
		if (pipe[i] == '<' || pipe[i] == '>')
		{
			if (i != 0)
				ft_lstadd_back(input, ft_lstnew(ft_strndup(pipe, i)));
			pipe = &pipe[i];
			i = 0;
			while (pipe[i] && (pipe[i] == '<' || pipe[i] == '>'))
				i++;
			ft_lstadd_back(input, ft_lstnew(ft_strndup(pipe, i)));
			pipe = &pipe[i];
			if (!pipe[0])
				break ;
			i = -1;
		}
	}
	ft_lstadd_back(input, ft_lstnew(ft_strdup(pipe)));
	return (TRUE);
}

int	check_redirection(t_list *input)
{
	char	*temp;

	temp = NULL;
	while (input)
	{
		temp = input->content;
		input->content = ft_strtrim(temp, " ");
		free(temp);
		temp = NULL;
		if (input->content[0] == '<' || input->content[0] == '>')
		{
			if (input->content[1] && input->content[0] != input->content[1])
				return (error_msg(0, &input->content[1]));
			else if (ft_strlen(input->content) > 2)
				return (error_msg(0, &input->content[2]));
			else if (input->next == NULL
			|| input->next->content[0] == '<' || input->next->content[0] == '>')
				return (error_msg(0, input->content));
		}
		input = input->next;
	}
	return (TRUE);
}

int	parse_redirection(t_list *input, t_info *info, t_list **cmd)
{
	int	infile;

	infile = 0;
	while (input)
	{
		if (input->content[0] == '<' || input->content[0] == '>')
		{
			if (ft_strncmp("<<", input->content, 3) == 0)
				info->limiter = delete_quot(input->next->content);
			else if (ft_strncmp("<", input->content, 2) == 0)
				ft_lstadd_back(&info->infile, ft_lstnew(delete_quot(input->next->content)));
			else if (ft_strncmp(">>", input->content, 3) == 0)
				ft_lstadd_back(&info->outfile_add, ft_lstnew(delete_quot(input->next->content)));
			else if (ft_strncmp(">", input->content, 2) == 0)
				ft_lstadd_back(&info->outfile, ft_lstnew(delete_quot(input->next->content)));
			input = input->next;
		}
		else
			ft_lstadd_back(cmd, ft_lstnew(delete_quot(input->content)));
		if (infile < 0 || info->outfile < 0)
			error_msg("open", 0);
		if (input)
			input = input->next;
	}
	return (TRUE);
}
