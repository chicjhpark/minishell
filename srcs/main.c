/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:13:03 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/20 21:26:16 by jaehpark         ###   ########.fr       */
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

/*int	handle_process(t_list *proc)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (error_msg("pipe"));
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (proc)
		{
			parse_command(proc->content);
			proc = proc->next;
		}
	}
	else if (pid > 0)
	{
		close(fd[1]);
		waitpid(pid, 0, WNOHANG);
	}
	else
		return (error_msg("fork"));
	return (TRUE);
}*/

int	check_token(t_list *token)
{
	while (token)
	{

	}
}

void	get_input(void)
{
	char	*input;
	t_list	*token;

	input = readline("$ ");
	token = NULL;
	if (input)
	{
		if (split_token(input, &token) == TRUE)
			if (check_token(token) == TRUE)
			{}
	}
	debug(token, "token");
	ft_lstclear(&token, free);
	ft_free(input);
}

int	main(void)
{
	t_set	set;

	init_set(&set);
	while (1)
	{
		get_input();
		reset_set(&set);
	}
	return (0);
}
