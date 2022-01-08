/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:13:03 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/09 02:07:17 by jaehpark         ###   ########.fr       */
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

int	check_builtin_command(t_list *cmd)
{
	if (ft_strncmp(cmd->content, "echo", 5) == 0 ||
		ft_strncmp(cmd->content, "cd", 3) == 0 ||
		ft_strncmp(cmd->content, "pwd", 4) == 0 ||
		ft_strncmp(cmd->content, "export", 7) == 0 ||
		ft_strncmp(cmd->content, "unset", 6) == 0 ||
		ft_strncmp(cmd->content, "env", 4) == 0 ||
		ft_strncmp(cmd->content, "exit", 5) == 0)
		return (TRUE);
	cmd = cmd->next;
	return (FALSE);
}

void	execute_builtin_command(t_proc *proc, char **exe)
{
	exe = &exe[1];
	printf("%s\n", exe[0]);
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

char	*ft_getenv(char *pre_env, char **env_lst)
{
	return (getenv(pre_env));
	env_lst = 0;
}

void	handler(int status)
{
	if (status == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_stat = 130;
	}
	if (status == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_stat = 131;
	}
}

void	parse_input(char *input, char **envp)
{
	t_list	*token;

	add_history(input);
	if (split_token(input, &token) == TRUE && check_token(token) == TRUE)
	{
		handle_heredoc(token);
		parse_pipe_token(token, envp);
		while (waitpid(-1, &g_stat, 0) > 0)
			continue ;
	}
	ft_lstclear(&token, free);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_set	set;
	char	*input;

	init_set(&set);
	signal(SIGQUIT, handler);
	signal(SIGINT, handler);
	while (1)
	{
		// signal(SIGQUIT, handler);
		// signal(SIGINT, handler);
		input = readline("$ ");
		if (!input)
		{
			reset_set(&set);
			exit(0);
		}
		parse_input(input, envp);
		input = ft_free(input);
		reset_stdio(&set);
		//system("leaks minishell");
	}
	return (0);
}
