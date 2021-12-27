/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:33:01 by jaehpark          #+#    #+#             */
/*   Updated: 2021/12/27 18:04:57 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>

# define ERROR		-1

typedef struct s_set
{
	struct termios	org_term;
	struct termios	new_term;
	int				org_stdin;
	int				org_stdout;
}t_set;

typedef struct s_proc
{
	t_list	*data;
	t_list	*cmd;
	t_list	*limiter;
	int		outfile;
}t_proc;

int		error_msg(char *msg);
void	*ft_free(char *p);
char	*ft_strntrim(char *s, char *set, int n);
char	*ft_strndup(char *s, int n);

void	init_set(t_set *set);
void	reset_set(t_set *set);

int		split_token(char *input, t_list **token);
int		split_rest_token(char *input, t_list **token);
int		split_pipe_token(char *input, int i, t_list **token);
int		split_space_token(char *input, int i, t_list **token);
int		split_redirection_token(char *input, int i, t_list **token);

int		find_valid_quot_point(char *line, int start);
int		find_env_var_point(char *line);

int		check_token(t_list *token);
int		handle_env_var(char *input);
char	*expand_env_var(char *data, int i);
int		make_process(t_list *token);
int		split_process(t_list *token);



#endif
