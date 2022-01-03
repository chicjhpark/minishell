/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:58:37 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/03 09:31:57 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_std_inout_redirection(t_proc *proc, t_list *data, char *temp)
{
	int	infile;

	if (ft_strncmp(data->content, "<", 3) == 0)
	{
		infile = open(temp, O_RDONLY);
		if (infile < 0)
		{
			error_msg(temp);
			ft_free(temp);
			return (ERROR);
		}
		dup2(infile, STDIN_FILENO);
	}
	if (ft_strncmp(data->content, ">>", 3) == 0)
		proc->outfile = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strncmp(data->content, ">", 2) == 0)
		proc->outfile = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (proc->outfile < 0)
	{
		error_msg(temp);
		ft_free(temp);
		return (ERROR);
	}
	return (TRUE);
}

int	parse_data(t_proc *proc, t_list *data)
{
	char	*temp;

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

int	parse_process(t_proc *proc)
{
	if (parse_data(proc, proc->data) == TRUE)
	{
		//handle_command(proc);
	}
	debug(proc->cmd, "cmd");
	ft_lstclear(&proc->limiter, free);
	ft_lstclear(&proc->cmd, free);
	ft_lstclear(&proc->data, free);
	return (TRUE);
}

int	parse_pipe_token(t_list *token)
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
			parse_process(&proc);
			ft_memset(&proc, 0, sizeof(t_proc));
		}
		token = token->next;
	}
	return (TRUE);
}

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
		parse_pipe_token(token);
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
