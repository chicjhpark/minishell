/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 05:41:46 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/09 06:16:44 by jaehpark         ###   ########.fr       */
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

int	check_builtin_command(t_list *cmd)
{
	if (ft_strncmp(cmd->content, "echo", 5) == 0
		|| ft_strncmp(cmd->content, "cd", 3) == 0
		|| ft_strncmp(cmd->content, "pwd", 4) == 0
		|| ft_strncmp(cmd->content, "export", 7) == 0
		|| ft_strncmp(cmd->content, "unset", 6) == 0
		|| ft_strncmp(cmd->content, "env", 4) == 0
		|| ft_strncmp(cmd->content, "exit", 5) == 0)
		return (TRUE);
	cmd = cmd->next;
	return (FALSE);
}

void	execute_builtin_command(t_proc *proc, char **exe)
{
	exe = &exe[1];
	if (ft_strncmp(proc->cmd->content, "echo", 5) == 0)
		ft_echo(exe);
	if (ft_strncmp(proc->cmd->content, "cd", 3) == 0)
		ft_cd(exe, proc->env_lst);
	if (ft_strncmp(proc->cmd->content, "pwd", 4) == 0)
		ft_pwd();
	if (ft_strncmp(proc->cmd->content, "export", 7) == 0)
		ft_export(exe, proc->env_lst);
	if (ft_strncmp(proc->cmd->content, "unset", 6) == 0)
		ft_unset(exe, &proc->env_lst);
	if (ft_strncmp(proc->cmd->content, "env", 4) == 0)
		ft_env(proc->env_lst);
	if (ft_strncmp(proc->cmd->content, "exit", 5) == 0)
		ft_exit(exe);
}

void	ft_replace_line(int var_stat)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_stat = var_stat;
}

void	handler(int status)
{
	pid_t	pid;

	pid = waitpid(-1, 0, WNOHANG);
	if (status == SIGINT)
	{
		if (pid == -1)
		{
			write(1, "\n", 1);
			ft_replace_line(1);
		}
		else
		{
			write(1, "\n", 1);
			g_stat = 130;
		}
	}
	else if (status == SIGQUIT && pid != -1)
	{
		write(1, "Quit: 3\n", 8);
		g_stat = 131;
	}
	else
		ft_replace_line(131);
}

void	parse_input(char *input, t_env *env, char **envp)
{
	t_list	*token;

	token = 0;
	add_history(input);
	if (split_token(input, &token) == TRUE && check_token(token) == TRUE)
	{
		handle_heredoc(token);
		parse_pipe_token(token, env, envp);
		while (waitpid(-1, &g_stat, 0) > 0)
			continue ;
	}
	if (WIFEXITED(g_stat))
		g_stat = WEXITSTATUS(g_stat);
	ft_lstclear(&token, free);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_set	set;
	t_env	*env;
	char	*input;

	env = env_set(envp);
	init_set(&set);
	while (1)
	{
		init_set2(&set);
		signal(SIGQUIT, handler);
		signal(SIGINT, handler);
		input = readline("$ ");
		if (!input)
		{
			reset_set(&set);
			exit(0);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &set.org_term);
		parse_input(input, env, envp);
		input = ft_free(input);
		reset_stdio(&set);
		//system("leaks minishell");
	}
	return (0);
}
