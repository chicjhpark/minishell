/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:08 by jaehpark          #+#    #+#             */
/*   Updated: 2021/11/25 18:32:38 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug(t_set *set, char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		printf("input [%d] : %s\n", i, input[i]);
		i++;
	}
}

int	init_input(t_set *set, char *line)
{
	int	i;
	int	j;
	int	num;

	i = -1;
	num = 0;
	while (line[++i])
		if (line[i] != ' ' && (!line[i + 1] || line[i + 1] == ' '))
			num++;
	set->input = (char **)malloc(sizeof(char *) * (num + 1));
	if (!set->input)
		return (error_msg("malloc"));
	i = -1;
	j = 0;
	while (line[++i])
	{
		num = 0;
		while (line[i] && line[i] != ' ')
		{
			i++;
			num++;
		}
		set->input[j] = (char *)malloc(sizeof(char) * (num + 1));
		if (!set->input[j])
			return (error_msg("malloc"));
		j++;
	}
	return (TRUE);
}

int	sort_input(t_set *set, char *line)
{
	int	i;
	int	j;
	int	k;

	if (init_input(set, line) == FALSE)
		return (FALSE);
	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		k = 0;
		while (line[i] && line[i] != ' ')
		{
			set->input[j][k] = line[i];
			i++;
			k++;
		}
		set->input[j][k] = '\0';
		j++;
	}
	set->input[j] = NULL;
	return (TRUE);
}

int	sort_redirection(t_set *set, char *line)
{
	char	*temp;
	int		i;

	temp = ft_strrchr(line, '<');
	if (temp != NULL && temp[1] == '<')
	{
		i = 2;
		while (temp[i] == ' ')
			i++;
		set->limiter =
	}
	else if (temp != NULL)
	{
		i = 1;
		while (temp[i] == ' ')
			i++;
		set->infile = open(&temp[i], O_RDONLY);
		if (set->infile < 0)
			return (error_msg("open"));
	}
	temp = ft_strrchr(line, '>');
	if (temp != NULL && temp[1] == '>')
	{
		i = 2;
		while (temp[i] == ' ')
			i++;
		set->outfile = open(&temp[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (set->outfile < 0)
			return (error_msg("open"));
	}
	else if (temp != NULL)
	{
		i = 1;
		while (temp[i] == ' ')
			i++;
		set->outfile = open(&temp[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (set->outfile < 0)
			return (error_msg("open"));
	}
	return (TRUE);
}

int	parse_input(t_set *set, char *line)
{
	set->input = ft_split(line, '|');
	if (sort_redirection(set, line) == FALSE)
		return (FALSE);
	if (sort_input(set, line) == FALSE)
		return (FALSE);
	debug(set, set->input);
	return (TRUE);
}

int	get_input(t_set *set)
{
	char	*line;

	line = readline("$ ");
	if (line)
	{
		if (parse_input(set, line) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int	main(void)
{
	t_set	set;

	init_set(&set);
	while (1)
	{
		if (get_input(&set) == FALSE)
		{
			free_set(&set);
			break ;
		}
		free_set(&set);
	}
	return (0);
}
