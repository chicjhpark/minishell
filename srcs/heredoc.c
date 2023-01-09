/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 08:14:17 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/09 06:08:12 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sum(char *line, char buf)
{
	int		size;
	char	*str;
	int		i;

	size = ft_strlen(line);
	str = (char *)malloc(sizeof(char) * (size + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] != 0)
	{
		str[i] = line[i];
		i++;
	}
	free(line);
	str[i++] = buf;
	str[i] = '\0';
	return (str);
}

int	get_next_line(char **line)
{
	char	buf;

	buf = '\0';
	*line = (char *)malloc(1);
	if (*line == NULL)
		return (-1);
	(*line)[0] = 0;
	read(0, &buf, 1);
	while (buf != '\n' && buf != '\0')
	{
		*line = sum(*line, buf);
		if (*line == 0)
			return (-1);
		read(0, &buf, 1);
	}
	if (buf == '\n')
		return (1);
	return (0);
}

void	print_line(char *line, char *limiter, int fd)
{
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		exit(0);
	write(1, "> ", 2);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int	heredoc(char *limiter)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	if (pipe(fd) == -1)
		return (error_msg("pipe"));
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		write(1, "> ", 2);
		while (get_next_line(&line))
			print_line(line, limiter, fd[1]);
		close(fd[1]);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, 0, 0);
		close(fd[0]);
	}
	else
		return (error_msg("fork"));
	return (TRUE);
}

void	handle_heredoc(t_list *token)
{
	int	org_stdin;

	org_stdin = dup(STDIN_FILENO);
	while (token)
	{
		if (strncmp(token->content, "<<", 3) == 0)
		{
			dup2(org_stdin, STDIN_FILENO);
			heredoc(token->next->content);
			token = token->next;
		}
		token = token->next;
	}
}
