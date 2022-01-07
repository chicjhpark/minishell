/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:13:03 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/08 03:05:49 by jaehpark         ###   ########.fr       */
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

void	*ft_free2(char **p)
{
	int	i;

	i = -1;
	while (p[++i])
	{
		if (p[i])
		{
			free(p[i]);
			p[i] = NULL;
		}
	}
	free(p[i]);
	free(p);
	return (NULL);
}

void	execute_builtin_command(t_list *cmd, char **exe, char **env_lst)
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
	cmd = cmd->next;
	ft_free2(exe);
}

/*char	*ft_getenv(char *pre_env, char **env_lst)
{

}*/

void	get_input(char **envp)
{
	char	*input;
	t_list	*token;

	input = readline("$ ");
	token = NULL;
	if (input)
	{
		add_history(input);
		if (split_token(input, &token) == TRUE && check_token(token) == TRUE)
		{
			handle_heredoc(token);
			parse_pipe_token(token, envp);
			while (wait(0) > 0)
			{
			}
		}
	}
	input = ft_free(input);
	ft_lstclear(&token, free);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_set	set;

	init_set(&set);
	while (1)
	{
		get_input(envp);
		reset_set(&set);
		//system("leaks minishell");
	}
	return (0);
}
