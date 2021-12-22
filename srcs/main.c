/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:13:03 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/22 17:23:28 by jaehpark         ###   ########.fr       */
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

int	find_env_var_point(char *line)
{
	int	find;

	find = 0;
	while (line[find] && (line[find] == '_' || ft_isalnum(line[find])))
		find++;
	return (find);
}

int	handle_env_var(t_list *data)
{
	char	*save;
	char	*temp1;
	char	*temp2;
	char	*temp3;
	char	*env_var;
	int		i;

	while (data)
	{
		i = -1;
		while (data->content[++i])
		{
			if (data->content[i] == '\'')
				i = find_valid_quot_point(data->content, i);
			if (data->content[i] == '$')
			{
				save = data->content;
				temp1 = ft_strndup(data->content, i);
				if (!temp1)
					return (error_msg("malloc"));
				data->content = &data->content[i + 1];
				i = find_env_var_point(data->content);
				temp2 = ft_strndup(data->content, i);
				if (!temp2)
				{
					ft_free(temp1);
					return (error_msg("malloc"));
				}
				data->content = &data->content[i];
				i = -1;
				env_var = getenv(temp2);
				ft_free(temp2);
				if (!env_var)
					temp3 = ft_strdup(temp1);
				else
				{
					temp3 = ft_strjoin(temp1, env_var);
					ft_free(env_var);
				}
				ft_free(temp1);
				if (!temp3)
					return (error_msg("malloc"));
				data->content = ft_strjoin(temp3, data->content);
				ft_free(temp3);
				if (!data->content)
					return (error_msg("malloc"));
				ft_free(save);
			}
		}
		data = data->next;
	}
	return (TRUE);
}

int	parse_proc(t_proc *proc)
{
	if (handle_env_var(proc->data) == TRUE)
	{
	}
	debug(proc->data, "data");
	ft_lstclear(&proc->data, free);
	return (TRUE);
}

int	handle_proc(t_list *token)
{
	t_proc	proc;
	char	*temp;

	ft_memset(&proc, 0, sizeof(t_proc));
	temp = NULL;
	while (token)
	{
		if (token->content[0] != '|')
		{
			temp = ft_strdup(token->content);
			if (!temp)
				return (error_msg("malloc"));
			ft_lstadd_back(&proc.data, ft_lstnew(temp));
		}
		if (!token->next || token->content[0] == '|')
		{
			parse_proc(&proc);
			ft_memset(&proc, 0, sizeof(t_proc));
		}
		token = token->next;
	}
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
		if (split_token(input, &token) == TRUE)
			if (check_token(token) == TRUE)
				if (handle_proc(token) == TRUE)
				{}
	}
	//debug(token, "token");
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
