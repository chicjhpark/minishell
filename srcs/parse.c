/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:58:37 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/28 09:01:32 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_process(t_list *token)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (error_msg("pipe"));
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		parse_process(token);
	}
	else if (pid > 0)
	{
		waitpid(pid, 0, WNOHANG);
		close(fd[1]);
		dup2(fd[0], STDOUT_FILENO);
	}
	else
	{
		close(fd[0]);
		close(fd[0]);
		return (error_msg("fork"));
	}
	return (TRUE);
}

int	parse_process(t_list *token)
{
	char	*temp;
	t_proc	proc;

	temp = NULL;
	ft_memset(&proc, 0, sizeof(t_proc));
	while (token)
	{
		if (token->content[0] != '|')
		{
			temp = ft_strdup(token->content);
			if (!temp)
				return (error_msg("malloc"));
			ft_lstadd_back(&proc.data, ft_lstnew(temp));
		}
		if (!token->next || token->content[0] == '|')
		{
			parse_data(&proc);
			ft_memset(&proc, 0, sizeof(t_proc));
		}
		token = token->next;
	}
	return (TRUE);
}

int	parse_std_inout_redirection(t_proc *proc, t_list *data, char *temp)
{
	int	infile;

	if (ft_strncmp(data->content, "<", 2) == 0)
	{
		infile = open(temp, O_RDONLY);
		ft_free(temp);
		if (infile < 0)
			return (error_msg("temp"));
		dup2(infile, STDIN_FILENO);
	}
	else if (data->content[0] == '>')
	{
		if (data->content[1] == '>')
			proc->outfile = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (!data->content[1])
			proc->outfile = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_free(temp);
		if (proc->outfile < 0)
			return (error_msg(temp));
	}
	return (TRUE);
}

int	handle_data(t_proc *proc, t_list *data)
{
	char	*temp;

	temp = NULL;
	while (data)
	{
		if (data->content[0] == '<' || data->content[0] == '>')
		{
			temp = expand_data(data->next->content);
			if (!temp)
				return (error_msg("malloc"));
			if (ft_strncmp(data->content, "<<", 3) == 0)
				ft_lstadd_back(&proc->limiter, ft_lstnew(temp));
			else if (parse_std_inout_redirection(proc, data, temp) == ERROR)
				return (ERROR);
			data = data->next;
		}
		else
		{
			temp = expand_data(data->content);
			if (!temp)
				return (error_msg("malloc"));
			ft_lstadd_back(&proc->cmd, ft_lstnew(temp));
		}
		data = data->next;
	}
	return (TRUE);
}
