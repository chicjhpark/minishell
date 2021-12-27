/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:58:37 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/27 18:04:51 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token(t_list *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->content[0] == '|' && (i == 0 ||
			!token->next || token->next->content[0] == '|'))
			return (error_msg("|"));
		else if (token->content[0] == '<' || token->content[0] == '>')
		{
			if (token->content[1] && token->content[0] != token->content[1])
				return (error_msg(&token->content[1]));
			else if (ft_strlen(token->content) > 2)
				return (error_msg(&token->content[2]));
			else if (!token->next)
				return (error_msg(NULL));
			else if (token->next->content[0] == '<' || token->next->content[0] == '>'
					|| token->next->content[0] == '|')
				return (error_msg(token->next->content));
		}
		i++;
		token = token->next;
	}
	return (TRUE);
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
		return (ft_free(temp));
	data = &data[i];
	get_env_var = getenv(pre_env_var);
	ft_free(pre_env_var);
	merge_env_var = ft_strjoin(temp, get_env_var);
	ft_free(temp);
	if (!merge_env_var)
		return (NULL);
	new_data = ft_strjoin(merge_env_var, data);
	ft_free(merge_env_var);
	return (new_data);
}

int	handle_env_var(char *input)
{
	char	*save;
	int		i;

		i = -1;
	while (input[++i])
	{
		if (input[i] == '\'')
			i = find_valid_quot_point(input, i);
		if (input[i] == '$')
		{
			save = input;
			input = expand_env_var(input, i);
			if (!input)
			{
				input = save;
				return (error_msg("malloc"));
			}
			ft_free(save);
			i = -1;
		}
	}
	return (TRUE);
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
		split_process(token);
	}
	else if (pid > 0)
	{
		waitpid(pid, 0, WNOHANG);
		close(fd[1]);
		dup2(fd[0], STDOUT_FILENO);
	}
	else
	{
		close(fd[0]);
		close(fd[0]);
		return (error_msg("fork"));
	}
	return (TRUE);
}

int	split_process(t_list *token)
{
	char	*temp;
	t_proc	proc;

	temp = NULL;
	ft_memset(&proc, 0, sizeof(t_proc));
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
