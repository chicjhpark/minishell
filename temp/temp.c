/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:19:17 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/15 16:18:36 by jaehpark         ###   ########.fr       */
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

int	check_special_mark(char *line, int *i)
{
	if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\"')
			(*i)++;
		if (!line[*i])
			return (error_msg(0, "\""));
	}
	else if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (!line[*i])
			return (error_msg(0, "\'"));
	}
	else if (line[*i] == ';')
		return (error_msg(0, ";"));
	else if (line[*i] == '\\')
		return (error_msg(0, "\\"));
	return (TRUE);
}

void	skip_quotation_mark(char *line, int *i)
{
	if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\"')
			(*i)++;
	}
	else if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
	}
}

void	skip_space(char **pipe, int *i, t_list **input)
{
	if ((*pipe)[*i] == ' ')
	{
		if (*i != 0)
			ft_lstadd_back(input, ft_lstnew(ft_strndup(*pipe, *i)));
		while ((*pipe)[*i] && (*pipe)[*i] == ' ')
			(*i)++;
		(*pipe) = &(*pipe)[*i];
		*i = 0;
	}
	skip_quotation_mark(*pipe, i);
}


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

char	*delete_quot(char *s)
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
	return (temp);
}

int	handle_redirection(t_info *info)
{
	int	fd;

	while (info->infile)
	{
		fd = open(info->infile->content, O_RDONLY);
		if (fd < 0)
			return (error_msg("open", 0));
		dup2(fd, STDIN_FILENO);
		info->infile = info->infile->next;
	}
	while (info->outfile)
	{
		fd = open(info->outfile->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (error_msg("open", 0));
		info->outfile = info->outfile->next;
		info->fd_outfile = fd;
	}
	while (info->outfile_add)
	{
		fd = open(info->outfile->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (error_msg("open", 0));
		info->outfile_add = info->outfile->next;
		info->fd_outfile = fd;
	}
	return (TRUE);
}

int	handle_heredoc(char *limiter)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	if (pipe(fd) == -1)
		return(error_msg("pipe", 0));
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
			print_line(line, limiter, fd[1]);
	}
	else if (pid > 0)
	{
		waitpid(pid, 0, WNOHANG);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
	else
		return (error_msg("fork", 0));
}

int	execute_command(t_list *cmd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (error_msg("pipe", 0));
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (execve(, cmd, envp) == -1)
			return (error_msg("execve", 0));
	}
	else if (pid > 0)
	{
		waitpid(pid, 0, WNOHANG);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
	else
		return (error_msg("fork", 0));
}

int	handle_command(t_info *info, t_list	*cmd)
{
	int	fd[2];

	if (info->limiter)
		if (handle_heredoc(info->limiter) == FALSE)
			return (FALSE);
	while (cmd)
	{
		if (execute_command(cmd) == FALSE);
			return (FALSE);
		cmd = cmd->next;
	}
	return (TRUE);
}

void	free_info(t_info *info)
{
	ft_lstclear(&info->infile, free);
	ft_lstclear(&info->outfile, free);
	ft_lstclear(&info->outfile_add, free);
	ft_lstclear(&info->cmd, free);
	free(info->limiter);
}

int	handle_pipe(char *pipe, int flag)
{
	t_list	*input;
	t_info	info;
	char	*save;

	input = NULL;
	ft_memset(&info, 0, sizeof(t_info));
	info.last_pipe = flag;
	save = pipe;
	if (parse_token(pipe, &input) == TRUE)
		if (check_redirection(input) == TRUE)
			if (parse_redirection(input, &info, &info.cmd) == TRUE)
				if (handle_redirection(&info) == TRUE)
					if (handle_command(&info, info.cmd) == FALSE)
					{
						pipe = save;
						free_info(&info);
						ft_lstclear(&input, free);
						return (FALSE);
					}
	pipe = save;
	debug(info.infile, "infile");
	debug(info.outfile_add, "outfile_add");
	debug(info.outfile, "outfile");
	debug(info.cmd, "cmd");
	free_info(&info);
	ft_lstclear(&input, free);
	return (TRUE);
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
				if (pipe->next == NULL)
					handle_pipe(pipe->content, TRUE);
				else
				{
					if (handle_pipe(pipe->content, FALSE) == FALSE)
						break ;
				}
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
