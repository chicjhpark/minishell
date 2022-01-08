/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:13:03 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/08 13:27:50 by jaehpark         ###   ########.fr       */
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
	/*if (ft_strncmp(cmd->content, "echo", 5) == 0 ||
		ft_strncmp(cmd->content, "cd", 3) == 0 ||
		ft_strncmp(cmd->content, "pwd", 4) == 0 ||
		ft_strncmp(cmd->content, "export", 7) == 0 ||
		ft_strncmp(cmd->content, "unset", 6) == 0 ||
		ft_strncmp(cmd->content, "env", 4) == 0 ||
		ft_strncmp(cmd->content, "exit", 5) == 0)
		return (TRUE);*/
	cmd = cmd->next;
	return (FALSE);
}

void	execute_builtin_command(t_proc *proc, char **exe, char **env_lst)
{
	/*if (ft_strncmp(cmd->content, "echo", 5) == 0)
		ft_echo(exe);
	if (ft_strncmp(cmd->content, "cd", 3) == 0)
		ft_cd(exe);
	if (ft_strncmp(cmd->content, "pwd", 4) == 0)
		ft_pwd(exe);
	if (ft_strncmp(cmd->content, "export", 7) == 0)
		ft_export(exe);
	if (ft_strncmp(cmd->content, "unset", 6) == 0)
		ft_unset(exe);
	if (ft_strncmp(cmd->content, "env", 4) == 0)
		ft_env(exe);
	if (ft_strncmp(cmd->content, "exit" 5) == 0)
		ft_exit(exe);*/
	env_lst = NULL;
	proc = NULL;
	ft_free2(exe);
}

char	*ft_getenv(char *pre_env, char **env_lst)
{
	if (pre_env[0] == '?')
		return ("[exit]");
	return (getenv(pre_env));
	env_lst = 0;
}

void	init_term(t_set *set)
{
	set->new_term.c_lflag &= 0;
	set->new_term.c_cc[VMIN] = 0;
	set->new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &set->org_term);
}

void	handler(int status)
{
	if (status == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		rl_on_new_line();
	}
}

void	handle_ctrl(char *input, t_set *set)
{
	if (!input)
	{
		//printf("exit\n");
		reset_set(set);
		exit(0);
	}
	//init_term(set);
}

void	parse_input(char *input, char **envp)
{
	t_list	*token;

	add_history(input);
	if (split_token(input, &token) == TRUE && check_token(token) == TRUE)
	{
		handle_heredoc(token);
		parse_pipe_token(token, envp);
		while (wait(0) > 0)
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
	while (1)
	{
		//signal(SIGINT, handler);
		input = readline("$ ");
		if (!input)
			handle_ctrl(input, &set);
		parse_input(input, envp);
		input = ft_free(input);
		reset_stdio(&set);
		//system("leaks minishell");
	}
	return (0);
}
