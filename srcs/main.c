/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:13:03 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/06 14:24:50 by jaehpark         ###   ########.fr       */
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
		dup2(STDOUT_FILENO, fd[0]);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		return (error_msg("fork"));
	}
	return (TRUE);
}

void	get_input(void)
{
	char	*input;
	t_list	*token;

	input = readline("$ ");
	//input = ft_strdup("ls");
	token = NULL;
	if (input)
	{
		add_history(input);
		if (split_token(input, &token) == TRUE
			&& check_token(token) == TRUE)
			parse_pipe_token(token);
			//make_process(token);
	}
	input = ft_free(input);
	ft_lstclear(&token, free);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_set	set;

	init_set(&set, envp);
	while (1)
	{
		get_input();
		reset_set(&set);
		//exit(0);
		//system("leaks minishell");
	}
	return (0);
}
