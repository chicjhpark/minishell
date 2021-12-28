/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:13:03 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/28 09:15:56 by jaehpark         ###   ########.fr       */
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

char	*del_quot_token(char *data, int i)
{
	char	*temp;
	int		quot1;
	int		quot2;
	int		j;

	temp = (char *)malloc(sizeof(char) * ft_strlen(data) + 1);
	if (!temp)
		return (NULL);
	quot1 = i;
	quot2 = find_valid_quot_point(data, i);
	i = -1;
	j = 0;
	while (data[++i])
		if (i != quot1 && i != quot2)
			temp[j++] = data[i];
	temp[j] = '\0';
	return (temp);
}

char	*expand_data(char *data)
{
	char	*temp;
	int		i;

	temp = ft_strdup(data);
	if (!temp)
		return (NULL);
	i = -1;
	while (data[++i])
	{
		if (data[i] == '\'')
			i = find_valid_quot_point(data, i);
		if (data[i] == '\"')
		{
			if (i != find_valid_quot_point(data, i))
			{
				temp = del_quot_token(data, i);
				if (!temp)
					return (NULL);
				data = expand_env_var(temp, i);
				printf("temp : %s\n", temp);
				ft_free(temp);
				temp = data;
				if (!data)
					return (NULL);
				i = -1;
			}
		}
		else if (data[i] == '$')
		{
			temp = expand_env_var(data, i);
			if (!temp)
				return (NULL);
			i = -1;
		}
	}
	return (temp);
}

int	parse_data(t_proc *proc)
{
	if (handle_data(proc, proc->data) == TRUE)
	{
	}
	debug(proc->cmd, "cmd");
	//debug(proc->data, "data");
	ft_lstclear(&proc->limiter, free);
	ft_lstclear(&proc->cmd, free);
	ft_lstclear(&proc->data, free);
	return (TRUE);
}

void	get_input(void)
{
	char	*input;
	t_list	*token;

	input = readline("$ ");
	token = NULL;
	if (input)
	{
		if (split_token(input, &token) && check_token(token))
			parse_process(token);
	}
	ft_free(input);
	ft_lstclear(&token, free);
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
