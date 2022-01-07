/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:33:01 by jaehpark          #+#    #+#             */
/*   Updated: 2022/01/07 14:00:46 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <termios.h>
# include <signal.h>
# include "libft.h"

# define ERROR		-1

char	**val_envp;

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
	int		infile;
	int		outfile;
	int		pip_flg;
}t_proc;

void	debug(t_list *lst, char *name);	// delete

int		error_msg(char *msg);
void	*ft_free(char *p);
char	*ft_strntrim(char *s, char *set, int n);
char	*ft_strndup(char *s, int n);

void	init_set(t_set *set, char **envp);
void	reset_set(t_set *set);

int		split_token(char *input, t_list **token);
int		split_rest_token(char *input, t_list **token);
int		split_pipe_token(char *input, int i, t_list **token);
int		split_space_token(char *input, int i, t_list **token);
int		split_redirection_token(char *input, int i, t_list **token);

int		find_valid_quot_point(char *data, int start);
int		find_env_var_token(char *data, int start, int end);
int		find_valid_env_var_point(char *data);
int		check_token(t_list *token);
char	*my_strtrim(char *data, int start, int end);

int		parse_pipe_token(t_list *token);
int		parse_process(t_proc *proc);
int		parse_last_process(t_proc *proc);
int		parse_data(t_proc *proc, t_list *data);
int		parse_std_inout_redirection(t_proc *proc, t_list *data, char *temp);

char	*expand_data(char *data);
char	*del_small_quot_token(char *data, int start, char **new_data);

int		heredoc(char *limiter);

int		handle_command(t_proc *proc, t_list *cmd);
int		handle_last_command(t_proc *proc, t_list *cmd);
char	**split_command(t_list *cmd);

int		check_builtin_command(t_list *cmd);
void	execute_builtin_command(t_list *cmd, char **exe);



#endif
