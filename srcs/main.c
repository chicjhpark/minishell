/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:13:03 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/24 02:45:46 by jaehpark         ###   ########.fr       */
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

char	*expand_env_var(char *data, int i)
{
	char	*temp;
	char	*pre_env_var;
	char	*get_env_var;
	char	*merge_env_var;
	char	*new_data;

	temp = ft_strndup(data, i);
	if (!temp)
		return (NULL);
	data = &data[i + 1];
	i = find_env_var_point(data);
	pre_env_var = ft_strndup(data, i);
	if (!pre_env_var)
		return (NULL);
	data = &data[i];
	get_env_var = getenv(pre_env_var);
	ft_free(pre_env_var);
	merge_env_var = ft_strjoin(temp, get_env_var);
	if (!merge_env_var)
		return (NULL);
	ft_free(temp);
	new_data = ft_strjoin(merge_env_var, data);
	return (new_data);
}

int	handle_env_var(t_list *data)
{
	char	*save;
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
				data->content = expand_env_var(data->content, i);
				if (!data->content)
				{
					data->content = save;
					return (error_msg("malloc"));
				}
				ft_free(save);
				i = -1;
			}
		}
		data = data->next;
	}
	return (TRUE);
}

int	handle_proc(t_proc *proc)
{
	if (handle_env_var(proc->data) == TRUE)
	{
	}
	debug(proc->data, "data");
	ft_lstclear(&proc->data, free);
	return (TRUE);
}

int	parse_proc(t_list *token)
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
			handle_proc(&proc);
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
				if (parse_proc(token) == TRUE)
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
