/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 00:33:29 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/10 00:33:33 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd, char **env_lst, int i)
{
	char	**paths;
	char	*path;
	char	*temp;

	while (env_lst[i] && ft_strnstr(env_lst[i], "PATH=", 5) == NULL)
		i++;
	if (env_lst[i] == NULL)
		return (cmd);
	paths = ft_split(env_lst[i] + 5, ':');
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
	return (cmd);
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

int	execute_command(t_proc *proc, t_list *cmd, int *fd, char **envp)
{
	char	**exe;

	close(fd[0]);
	if (proc->outfile > 0)
		dup2(proc->outfile, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exe = split_command(cmd);
	if (!exe)
		return (error_msg("malloc"));
	if (check_builtin_command(proc->cmd) == TRUE)
		execute_builtin_command(proc, exe);
	else if (exe[0][0] == '/' || exe[0][0] == '.')
	{
		if (execve(exe[0], exe, 0) == -1)
			return (error_msg(exe[0]));
	}
	else if (execve(find_path(exe[0], envp, 0), exe, envp) == -1)
		return (error_msg(exe[0]));
	return (0);
}

int	handle_command(t_proc *proc, t_list *cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (error_msg("pipe"));
	pid = fork();
	if (pid == 0)
		exit(execute_command(proc, cmd, fd, envp));
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		return (error_msg("fork"));
	}
	return (0);
}

int	handle_last_command(t_proc *proc, t_list *cmd, char **envp)
{
	pid_t	pid;
	char	**exe;

	pid = fork();
	if (pid == 0)
	{
		if (proc->outfile > 0)
			dup2(proc->outfile, STDOUT_FILENO);
		exe = split_command(cmd);
		if (!exe)
			return (error_msg("malloc"));
		if (check_builtin_command(proc->cmd) == TRUE)
			execute_builtin_command(proc, exe);
		else if (exe[0][0] == '/' || exe[0][0] == '.')
			proc->status = execve(exe[0], exe, envp);
		else
			proc->status = execve(find_path(exe[0], envp, 0), exe, envp);
		if (proc->status == -1)
			exit(error_msg(exe[0]));
	}
	else if (pid > 0)
		return (0);
	else
		return (error_msg("fork"));
	return (0);
}
