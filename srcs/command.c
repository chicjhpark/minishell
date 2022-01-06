/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:15:53 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/07 01:47:49 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	while (ft_strnstr(val_envp[i], "PATH=", 5) == NULL)
		i++;
	paths = ft_split(val_envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = NULL;
		path = ft_strjoin(paths[i], "/");
		temp = path;
		path = ft_strjoin(path, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			free(paths);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	**split_command(t_list *cmd)
{
	char	**exe;
	int		size;
	int		i;

	size = ft_lstsize(cmd);
	exe = (char **)malloc(sizeof(char *) * (size + 1));
	if (!exe)
		return (NULL);
	i = 0;
	while (i < size)
	{
		exe[i] = cmd->content;
		cmd = cmd->next;
		i++;
	}
	exe[i] = NULL;
	return (exe);
}

int	handle_command(t_proc *proc, t_list *cmd)
{
	int		fd[2];
	pid_t	pid;
	char	**exe;

	if (pipe(fd) == -1)
		return (error_msg("pipe"));
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (proc->outfile > 0)
			dup2(proc->outfile, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
		exe = split_command(cmd);
		if (!exe)
			return (error_msg("malloc"));
		if (strncmp(exe[0], "exit", 5) == 0)
			exit(0);
		if (exe[0][0] == '/' || exe[0][0] == '.')
			if (execve(exe[0], exe, val_envp) == -1)
				return (error_msg(exe[0]));
		close(fd[1]);
		if (execve(find_path(exe[0]), exe, val_envp) == -1)
			return (error_msg(exe[0]));
		exit(0);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, 0, WNOHANG);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		return (error_msg("fork"));
	}
	return (TRUE);
}

int	handle_last_command(t_proc *proc)
{
	pid_t	pid;
	char	**exe;

	if (parse_data(proc, proc->data) == TRUE && proc->cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			if (proc->outfile > 0)
				dup2(proc->outfile, STDOUT_FILENO);
			exe = split_command(proc->cmd);
			if (!exe)
				return (error_msg("malloc"));
			if (strncmp(exe[0], "exit", 5) == 0)
				exit(0);
			if (exe[0][0] == '/' || exe[0][0] == '.')
				if (execve(exe[0], exe, val_envp) == -1)
					return (error_msg(exe[0]));
			if (execve(find_path(exe[0]), exe, val_envp) == -1)
				return (error_msg(exe[0]));
		}
		else if (pid > 0)
		{
			waitpid(pid, 0, 0);
			//dup2(fd[0], STDOUT_FILENO);
			//dup2(proc->outfile, STDOUT_FILENO);
		}
		else
		{
			return (error_msg("fork"));
		}
	}
	ft_lstclear(&proc->limiter, free);
	ft_lstclear(&proc->cmd, free);
	ft_lstclear(&proc->data, free);
	return (TRUE);
}