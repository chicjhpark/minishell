/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:58:37 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/09 22:15:11 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_std_inout_redirection(t_proc *proc, t_list *data, char *temp)
{
	if (ft_strncmp(data->content, "<<", 3) == 0)
		ft_lstadd_back(&proc->limiter, ft_lstnew(temp));
	if (ft_strncmp(data->content, "<", 3) == 0)
	{
		proc->infile = open(temp, O_RDONLY);
		if (proc->infile < 0)
		{
			error_msg(temp);
			ft_free(temp);
			return (ERROR);
		}
		dup2(proc->infile, STDIN_FILENO);
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
			temp = expand_data(proc, data->next->content);
			if (!temp)
				return (error_msg("malloc"));
			else if (parse_std_inout_redirection(proc, data, temp) == ERROR)
				return (ERROR);
			ft_free(temp);
			data = data->next;
		}
		else
		{
			temp = expand_data(proc, data->content);
			if (!temp)
				return (error_msg("malloc"));
			ft_lstadd_back(&proc->cmd, ft_lstnew(temp));
		}
		data = data->next;
	}
	return (TRUE);
}

int	parse_process(t_proc *proc, t_env *env, char **envp)
{
	proc->env_lst = env;
	if (parse_data(proc, proc->data) == TRUE && proc->cmd)
		handle_command(proc, proc->cmd, envp);
	ft_lstclear(&proc->limiter, free);
	ft_lstclear(&proc->cmd, free);
	ft_lstclear(&proc->data, free);
	return (TRUE);
}

int	parse_last_process(t_proc *proc, t_env *env, char **envp)
{
	char	**exe;

	proc->env_lst = env;
	exe = NULL;
	if (parse_data(proc, proc->data) == TRUE && proc->cmd)
	{
		if (proc->pip_flg == FALSE && check_builtin_command(proc->cmd) == TRUE)
		{
			if (proc->outfile > 0)
				dup2(proc->outfile, STDOUT_FILENO);
			exe = split_command(proc->cmd);
			if (!exe)
				return (error_msg("malloc"));
			execute_builtin_command(proc, exe);
		}
		else
			handle_last_command(proc, proc->cmd, envp);
	}
	ft_lstclear(&proc->limiter, free);
	ft_lstclear(&proc->cmd, free);
	ft_lstclear(&proc->data, free);
	return (TRUE);
}

int	parse_pipe_token(t_list *token, t_env *env, char **envp)
{
	char	*temp;
	t_proc	proc;

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
		if (token->content[0] == '|')
		{
			parse_process(&proc, env, envp);
			ft_memset(&proc, 0, sizeof(t_proc));
			proc.pip_flg = TRUE;
		}
		if (!token->next)
			parse_last_process(&proc, env, envp);
		token = token->next;
	}
	return (TRUE);
}
